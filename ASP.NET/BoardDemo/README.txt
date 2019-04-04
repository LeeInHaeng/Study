# 사용 라이브러리
- Ninject : DI 컨테이너 사용
  - Ninject
  - Ninject.Web.Common.WebHost
  - Ninject.MVC5 
- Jquery : Ajax 기능 사용
  - jQuery
  - Microsoft.jQuery.Unobtrusive.Ajax
- Bootstrap : CSS 기능 사용
  - bootstrap 3.3.0 버전
- PagedList : 페이징 처리 기능을 위해 사용
  - PagedList.Mvc
- Dapper : ORM 및 SQL 사용
  - Dapper
  - 참조 추가 : System.Configuration
- 유효성 검사 추가
  - 참조 추가 : System.ComponentModel.DataAnnotations

# DB 연동 및 설계
- 서버 탐색기 ---> SQL Server 추가 ---> 로컬 ---> MSSQLLocalDB
- SQL Server 개체 탐색기 에서 (localdb) 이름 확인
  - (localdb)\MSSQLLocalDB
- 서버 탐색기 ---> 데이터베이스에 연결 아이콘 클릭
- 데이터 소스를 Microsoft SQL Server로 선택 후 Continue
- Server name은 처음에 확인했던 (localdb)\MSSQLLocalDB 으로 지정함으로써 LocalDB 기능을 사용
- 인증은 Windows 인증, 데이터베이스 이름 작성
- 게시판 (Board)
  - bid, 제목, 내용, 작성자, 등록 날짜, 카테고리, 댓글수, 추천수
```
CREATE TABLE Board(
	bid BIGINT NOT NULL PRIMARY KEY IDENTITY,
	title NVARCHAR(100) NOT NULL,
	content NVARCHAR(500) NOT NULL,
	writer NVARCHAR(100) NOT NULL,
	regDate DATETIME NOT NULL DEFAULT GETDATE(),
	category VARCHAR(20) NOT NULL DEFAULT 'ALL',
	rCnt BIGINT NOT NULL DEFAULT 0,
	recomCnt BIGINT NOT NULL DEFAULT 0
);
```
- 댓글 (Replies)
  - rid, 내용, 작성자, 등록 날짜, 추천수, Board 외래키, 댓글 그룹번호(답글 처리용), 부모 댓글번호(답글 처리용)
```
CREATE TABLE Replies(
	rid BIGINT NOT NULL PRIMARY KEY IDENTITY,
	content NVARCHAR(500) NOT NULL,
	writer NVARCHAR(100) NOT NULL,
	regDate DATETIME NOT NULL DEFAULT GETDATE(),
	recomCnt BIGINT NOT NULL DEFAULT 0,
	foreignBoard BIGINT FOREIGN KEY REFERENCES Board(bid) ON DELETE CASCADE,
	groupId BIGINT NOT NULL,
	pid BIGINT NOT NULL
);
```

# DB를 바탕으로 Model 클래스 설계
- 게시판
```
    public class Board
    {
        public Int64 bid { get; set; }
        public string title { get; set; }
        public string content { get; set; }
        public string writer { get; set; }
        public DateTime regDate { get; set; }
        public string category { get; set; }
        public Int64 rCnt { get; set; }
        public Int64 recomCnt { get; set; }
    }
```
- 댓글
```
    public class Replies
    {
        public Int64 rid { get; set; }
        public string content { get; set; }
        public string writer { get; set; }
        public DateTime regDate { get; set; }
        public Int64 recomCnt { get; set; }
        public Int64 foreignBoard { get; set; }
        public Int64 groupId { get; set; }
        public Int64 pid { get; set; }
    }
```
- 제약 조건
```
        [StringLength(100, ErrorMessage = "제목의 최대 길이는 {1} 입니다.")]
        [Required(ErrorMessage = "제목을 입력해 주세요.")]
        [Display(Name = "제목")]
        public string title { get; set; }

	...
```

# CRUD 관련 Repository와 RepositoryImpl 구현
- Web.config에서 DB 연동
```
  <connectionStrings>
    <add name="ConnectionString" connectionString="Data Source=(localdb)\MSSQLLocalDB; 
         Initial Catalog=BoardPractice; Integrated Security=True"
         providerName="System.Data.SqlClient"/>
  </connectionStrings>
```
- CRUD 관련 기능 Repository 설계
  - CRUD 외에 구현해야할 기능이 생기면 인터페이스와 구현 클래스를 함께 수정
```
    public interface DapperBoardRepository
    {
        void AddBoard(Board b);
        void EditBoard(Board b);
        void RemoveBoard(Int64 bid);
        IEnumerable<Board> GetBoard();
    }
```
- Repository 인터페이스 구현
  - Dapper 사용
```
using Dapper;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

public class DapperBoardRepositoryImpl : DapperBoardRepository
    {
        private IDbConnection db = new SqlConnection(
            ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);

	// 인터페이스 구현
	...
```

# DI 컨테이너 사용을 위해 Ninject 설정
- NinjectDependencyResolver 클래스 생성 후 인터페이스 구현
```
using Ninject;
using System.Web.Mvc;
using BoardDemo.Models.Repository;

    public class NinjectDependencyResolver : IDependencyResolver
    {
        private IKernel kernel;

        public NinjectDependencyResolver(IKernel kernelParam)
        {
            kernel = kernelParam;
            AddBindings();
        }

        public object GetService(Type serviceType)
        {
            return kernel.TryGet(serviceType);
        }

        public IEnumerable<object> GetServices(Type serviceType)
        {
            return kernel.GetAll(serviceType);
        }

        private void AddBindings()
        {
            kernel.Bind<DapperBoardRepository>().To<DapperBoardRepositoryImpl>();
        }
    }
```
- App_Start/NinjectWebCommon.cs 에서 RegisterServices 메소드 구현
```
    using Ninject.Web.Common.WebHost;
    using Models.Utils;

        private static void RegisterServices(IKernel kernel)
        {
            System.Web.Mvc.DependencyResolver.SetResolver(
                new NinjectDependencyResolver(kernel));
        }  
```
- Controller에서 인터페이스 Repository 사용 (생성자 등록)
```
    public class HomeController : Controller
    {
        private DapperBoardRepository repo;

        public HomeController(DapperBoardRepository repoParam)
        {
            repo = repoParam;
        }

	...
```

# 페이징 처리 : PagedList 사용
- Controller 에서
```
using PagedList;

        public ActionResult Index(string category, int? page)
        {
            int pageNo = page ?? 1;
            var viewData = repo.GetBoard()
                .Where(b => b.category == category || category == null);
            ViewBag.category = category ?? null;

            return View(viewData.ToPagedList(pageNo, pageSize));
        }
```
- View 에서
```
@using PagedList.Mvc
@model PagedList.IPagedList<BoardDemo.Models.Board>

<link href="~/Content/PagedList.css" rel="stylesheet" type="text/css" />

                @foreach(var b in Model)
                {
                    <tr>
                        <td>@b.regDate.ToString("yyyy-MM-dd hh:mm")</td>
			...
                    </tr>
                }

    <div>
        @Html.PagedListPager(Model, page => Url.Action("Index",
                                        new { page, category = ViewBag.category }))
    </div>
```
- App_Start/RouteConfig.cs 설정
```
            routes.MapRoute(
                name: null,
                url: "{controller}/page{page}",
                defaults: new { controller = "board", action = "Index", category = (string)null },
                constraints: new { page = @"\d+"}
            );

            routes.MapRoute(
                name: null,
                url: "{controller}/{category}",
                defaults: new { controller = "board", action = "Index", page = 1 },
                constraints: new { category = "ALL|NOTICE"}
            );

            routes.MapRoute(
                name: null,
                url: "{controller}/{category}/page{page}",
                defaults: new { controller = "board", action = "Index" },
                constraints: new { category = "ALL|NOTICE", page = @"\d+" }
            );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );
```

# 한글 깨짐 및 TempData 처리
- MSSQL 한글 깨짐 해결
  - 컬럼 타입을 NVARCHAR 타입으로 지정한다.
  - INSERT 구문시 NVARCHAR 타입은 N'한글 데이터' 식으로 데이터를 삽입한다.
- TempData 처리
```
// controller
TempData["result"] = "registerSuccess";

// Razor javascript
    <script type="text/javascript" language="javascript">
        if('@TempData["result"]' !== ''){
            alert('@TempData["result"]');
            @TempData["result"] = "";
        }

    </script>
```

# Model 클래스를 바탕으로 Form 태그 작성 및 유효성 검사
- Register.cshtml 참고
- Model에서 Required 사용
```
[Required(ErrorMessage = "제목을 입력해 주세요.")]
```
- View에서 Model 클래스를 바탕으로 Form 태그 생성
  - Html.ValidationMessage를 이용해 Model에서 선언한 Required 확인
```
        @using (Html.BeginForm("Register", "board", FormMethod.Post))
        {
            //@Html.HttpMethodOverride(HttpVerbs.Put)

            foreach (var p in ViewData.ModelMetadata.Properties)
            {
                        <div class="form-group">
                            <label>@p.DisplayName</label>
                            @Html.TextBox(@p.PropertyName, null, new { @class = "form-control" })
                            @Html.ValidationMessage(@p.PropertyName, "제목을 입력해 주세요.")
                        </div>
			...
	    }
		<input class="btn btn-primary" type="submit" value="글 작성 완료" />
	}
```
- Controller에서 유효성 검사 체크
```
        public ActionResult Register(Board b)
        {
            if (ModelState.IsValid)
            {
                return RedirectToAction("Index");
            }
            else
                return View();    
        }
```

# Ajax 헬퍼 메소드 사용
- NuGet에서 jQuery와 Microsoft.jQuery.Unobtrusive 설치
- Web.config 파일에서 Ajax 기능을 활성화 시킨다.
  - appSettings 태그 안에서
```
<add key="UnobtrusiveJavaScriptEnabled" value="true" /> 로 지정
```
- cshtml에서 jQuery 사용
```
    <script src="~/scripts/jquery-3.3.1.js"></script>
    <script src="~/scripts/jquery.unobtrusive-ajax.js"></script>
```
- Ajax를 이용해 부분적으로 View를 바로 업데이트 하기 위해 부분 뷰에 대한 cshtml 생성
- 이때 Ajax.BeginForm 이나 Ajax.ActionLink 등의 기능을 사용하며 Ajax 옵션 설정
- UpdateTargetId에 업데이트할 태그 영역의 ID를 적어준다.
```
@model IEnumerable<BoardDemo.Models.Replies>

@{ 
    AjaxOptions ajaxOpts = new AjaxOptions
    {
        UpdateTargetId = "replBody",
        OnSuccess = "registerRepl"
    };
}

@using (Ajax.BeginForm("register", "repl", ajaxOpts))
{
    <div class="form-group">
        <label>댓글</label>
        <span id="rCnt" class="badge">(@Model.Count())</span>
        @Html.TextArea("replArea", null,
                            new { @class = "form-control", rows = 1, required = "required" })
    </div>
    @Html.Hidden("bid",Model.FirstOrDefault().foreignBoard)
    <input class="btn btn-primary" type="submit" value="댓글 작성" />
}


@foreach (var r in Model)
{
    if (@r.pid == -1)
    {
        <div id="repl_@r.rid">
            <div>
                <span>@r.writer</span>
                <span>@r.regDate</span>
                <span>@r.recomCnt</span>
                <span>
                    @Ajax.ActionLink("댓글 삭제", "delete",
                    new { rid = @r.rid },
                    new AjaxOptions
                    {
                        UpdateTargetId = "replBody",
                        OnSuccess = "deleteRepl"
                    }, new { @class = "btn btn-danger" })
                </span>
            </div>
            <div>
                @r.content
            </div>
        </div>
    }

}
```
- 컨트롤러에서 PartialViewResult를 반환
```
        public PartialViewResult GetRepl(Int64 bid)
        {
            var data = repo.GetRepl(bid);
            return PartialView(data);
        }

        public PartialViewResult delete(Int64 rid)
        {
            int replParent = repo.GetReplParent(rid);

            repo.RemoveRepl(rid);
            repo2.decRcnt(replParent);

            var data = repo.GetRepl(replParent);
            return PartialView("GetRepl", data);
        }
```
- 다른 cshtml에서 부분 뷰의 cshtml에 해당되는 컨트롤러와 액션메소드 호출
```
            <div id="replBody">
                @Html.Action("GetRepl", "repl", new { bid = Model.bid })
            </div>
```
