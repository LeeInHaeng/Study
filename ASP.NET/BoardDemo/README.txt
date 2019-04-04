# ��� ���̺귯��
- Ninject : DI �����̳� ���
  - Ninject
  - Ninject.Web.Common.WebHost
  - Ninject.MVC5 
- Jquery : Ajax ��� ���
  - jQuery
  - Microsoft.jQuery.Unobtrusive.Ajax
- Bootstrap : CSS ��� ���
  - bootstrap 3.3.0 ����
- PagedList : ����¡ ó�� ����� ���� ���
  - PagedList.Mvc
- Dapper : ORM �� SQL ���
  - Dapper
  - ���� �߰� : System.Configuration
- ��ȿ�� �˻� �߰�
  - ���� �߰� : System.ComponentModel.DataAnnotations

# DB ���� �� ����
- ���� Ž���� ---> SQL Server �߰� ---> ���� ---> MSSQLLocalDB
- SQL Server ��ü Ž���� ���� (localdb) �̸� Ȯ��
  - (localdb)\MSSQLLocalDB
- ���� Ž���� ---> �����ͺ��̽��� ���� ������ Ŭ��
- ������ �ҽ��� Microsoft SQL Server�� ���� �� Continue
- Server name�� ó���� Ȯ���ߴ� (localdb)\MSSQLLocalDB ���� ���������ν� LocalDB ����� ���
- ������ Windows ����, �����ͺ��̽� �̸� �ۼ�
- �Խ��� (Board)
  - bid, ����, ����, �ۼ���, ��� ��¥, ī�װ�, ��ۼ�, ��õ��
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
- ��� (Replies)
  - rid, ����, �ۼ���, ��� ��¥, ��õ��, Board �ܷ�Ű, ��� �׷��ȣ(��� ó����), �θ� ��۹�ȣ(��� ó����)
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

# DB�� �������� Model Ŭ���� ����
- �Խ���
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
- ���
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
- ���� ����
```
        [StringLength(100, ErrorMessage = "������ �ִ� ���̴� {1} �Դϴ�.")]
        [Required(ErrorMessage = "������ �Է��� �ּ���.")]
        [Display(Name = "����")]
        public string title { get; set; }

	...
```

# CRUD ���� Repository�� RepositoryImpl ����
- Web.config���� DB ����
```
  <connectionStrings>
    <add name="ConnectionString" connectionString="Data Source=(localdb)\MSSQLLocalDB; 
         Initial Catalog=BoardPractice; Integrated Security=True"
         providerName="System.Data.SqlClient"/>
  </connectionStrings>
```
- CRUD ���� ��� Repository ����
  - CRUD �ܿ� �����ؾ��� ����� ����� �������̽��� ���� Ŭ������ �Բ� ����
```
    public interface DapperBoardRepository
    {
        void AddBoard(Board b);
        void EditBoard(Board b);
        void RemoveBoard(Int64 bid);
        IEnumerable<Board> GetBoard();
    }
```
- Repository �������̽� ����
  - Dapper ���
```
using Dapper;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

public class DapperBoardRepositoryImpl : DapperBoardRepository
    {
        private IDbConnection db = new SqlConnection(
            ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);

	// �������̽� ����
	...
```

# DI �����̳� ����� ���� Ninject ����
- NinjectDependencyResolver Ŭ���� ���� �� �������̽� ����
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
- App_Start/NinjectWebCommon.cs ���� RegisterServices �޼ҵ� ����
```
    using Ninject.Web.Common.WebHost;
    using Models.Utils;

        private static void RegisterServices(IKernel kernel)
        {
            System.Web.Mvc.DependencyResolver.SetResolver(
                new NinjectDependencyResolver(kernel));
        }  
```
- Controller���� �������̽� Repository ��� (������ ���)
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

# ����¡ ó�� : PagedList ���
- Controller ����
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
- View ����
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
- App_Start/RouteConfig.cs ����
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

# �ѱ� ���� �� TempData ó��
- MSSQL �ѱ� ���� �ذ�
  - �÷� Ÿ���� NVARCHAR Ÿ������ �����Ѵ�.
  - INSERT ������ NVARCHAR Ÿ���� N'�ѱ� ������' ������ �����͸� �����Ѵ�.
- TempData ó��
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

# Model Ŭ������ �������� Form �±� �ۼ� �� ��ȿ�� �˻�
- Register.cshtml ����
- Model���� Required ���
```
[Required(ErrorMessage = "������ �Է��� �ּ���.")]
```
- View���� Model Ŭ������ �������� Form �±� ����
  - Html.ValidationMessage�� �̿��� Model���� ������ Required Ȯ��
```
        @using (Html.BeginForm("Register", "board", FormMethod.Post))
        {
            //@Html.HttpMethodOverride(HttpVerbs.Put)

            foreach (var p in ViewData.ModelMetadata.Properties)
            {
                        <div class="form-group">
                            <label>@p.DisplayName</label>
                            @Html.TextBox(@p.PropertyName, null, new { @class = "form-control" })
                            @Html.ValidationMessage(@p.PropertyName, "������ �Է��� �ּ���.")
                        </div>
			...
	    }
		<input class="btn btn-primary" type="submit" value="�� �ۼ� �Ϸ�" />
	}
```
- Controller���� ��ȿ�� �˻� üũ
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

# Ajax ���� �޼ҵ� ���
- NuGet���� jQuery�� Microsoft.jQuery.Unobtrusive ��ġ
- Web.config ���Ͽ��� Ajax ����� Ȱ��ȭ ��Ų��.
  - appSettings �±� �ȿ���
```
<add key="UnobtrusiveJavaScriptEnabled" value="true" /> �� ����
```
- cshtml���� jQuery ���
```
    <script src="~/scripts/jquery-3.3.1.js"></script>
    <script src="~/scripts/jquery.unobtrusive-ajax.js"></script>
```
- Ajax�� �̿��� �κ������� View�� �ٷ� ������Ʈ �ϱ� ���� �κ� �信 ���� cshtml ����
- �̶� Ajax.BeginForm �̳� Ajax.ActionLink ���� ����� ����ϸ� Ajax �ɼ� ����
- UpdateTargetId�� ������Ʈ�� �±� ������ ID�� �����ش�.
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
        <label>���</label>
        <span id="rCnt" class="badge">(@Model.Count())</span>
        @Html.TextArea("replArea", null,
                            new { @class = "form-control", rows = 1, required = "required" })
    </div>
    @Html.Hidden("bid",Model.FirstOrDefault().foreignBoard)
    <input class="btn btn-primary" type="submit" value="��� �ۼ�" />
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
                    @Ajax.ActionLink("��� ����", "delete",
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
- ��Ʈ�ѷ����� PartialViewResult�� ��ȯ
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
- �ٸ� cshtml���� �κ� ���� cshtml�� �ش�Ǵ� ��Ʈ�ѷ��� �׼Ǹ޼ҵ� ȣ��
```
            <div id="replBody">
                @Html.Action("GetRepl", "repl", new { bid = Model.bid })
            </div>
```
