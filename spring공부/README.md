# Springboot 사용 라이브러리 (메이븐)
- DevTools
- Lombok
- MyBatis
- Thymeleaf
- Web
- PostgreSQL

# PostgreSQL 설치 및 설계
- 설치
  - https://www.tutorialspoint.com/postgresql/postgresql_environment.htm
- 한글 처리
```
set server_encoding = 'UTF8';
set client_encoding = 'UTF8';
CREATE DATABASE [[디비 이름]] TEMPLATE template0 LC_COLLATE 'C';
```

- 설계시 컬럼 타입 참고
  - https://www.tutorialspoint.com/postgresql/postgresql_data_types.htm
```
CREATE TABLE Board(
	bid BIGSERIAL PRIMARY KEY NOT NULL,
	title VARCHAR(50) NOT NULL,
	content VARCHAR(500) NOT NULL,
	writer VARCHAR(50) NOT NULL,
	regDate TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
	category VARCHAR(20) DEFAULT 'ALL',
	rCnt BIGINT DEFAULT 0,
	recomCnt BIGINT DEFAULT 0
);

CREATE TABLE Replies(
	rid BIGSERIAL PRIMARY KEY NOT NULL,
	content VARCHAR(500) NOT NULL,
	writer VARCHAR(50) NOT NULL,
	regDate TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
	recomCnt BIGINT DEFAULT 0,
	fbid BIGINT REFERENCES Board(bid) ON DELETE CASCADE,
	groupId BIGINT DEFAULT nextval(pg_get_serial_sequence('Replies', 'rid'))-1,
	pid BIGINT DEFAULT -1
);
```
- 해당 데이터베이스를 바탕으로 DTO 클래스 파일 작성
  - lombok에서 getter, setter 메소드를 만들어주지 않을 경우
  - Maven Dependencies에서 lombok.jar가 설치되어 있는 경로로 이동 후 jar 파일 실행
  - C:\Users\lih\.m2\repository\org\projectlombok\lombok\1.18.6
  - eclipse.exe선택, lombok 설치 후 이클립스 재시작
```
@Data
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Board {
```

# SpringBoot PostgreSQL Mybatis 연동
- src/main/resources/application.properties 파일에 dataSource 등록
```
spring.datasource.driver-class-name=org.postgresql.Driver
spring.datasource.url=jdbc:postgresql://localhost:5432/postgres
spring.datasource.username=postgres
spring.datasource.password=1234
```
- SpringBootApplication 클래스 파일에서
  - 나중에 DAO 인터페이스를 Autowired 하기 위해 MapperScan에 등록
  - SqlSessionFactory를 이용해 Mapper.xml 파일 로드
```
@SpringBootApplication
@MapperScan(value = {"com.demo.repo"})
public class BoardDemoSpringbootApplication {

	public static void main(String[] args) {
		SpringApplication.run(BoardDemoSpringbootApplication.class, args);
	}
    
     // SqlSessionFactory Setting
    @Bean
    public SqlSessionFactory sqlSessionFactory(DataSource dataSource)throws Exception{
        SqlSessionFactoryBean sessionFactory = new SqlSessionFactoryBean();
            sessionFactory.setDataSource(dataSource);
            
            Resource[] res = new PathMatchingResourcePatternResolver().getResources("classpath:mappers/*Mapper.xml");
            
            sessionFactory.setMapperLocations(res);
            
            return sessionFactory.getObject();
    }
}

```
- DTO 클래스를 바탕으로 DAO 인터페이스 생성
  - mybatis를 사용할 경우 : Mapper 어노테이션 사용
```
@Mapper
public interface BoardDAO {

	public void insertBoard(Board b);
```
- Mybatis를 이용한 xml 파일 작성
  - resources 폴더 아래 mappers 폴더 생성 후 xml 파일 작성
  - mapper namespace : 쿼리와 맵핑할 인터페이스의 경로를 적어준다.
  - id : 맵핑하고자 하는 메소드 명을 적어준다.
  - resultType : 반환할 타입의 클래스 경로를 적어준다.
  - parameterType : 매개변수로 받을 타입을 지정
```
<?xml version="1.0" encoding="UTF-8"?>

<!DOCTYPE mapper PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">

<mapper namespace="com.demo.repo.BoardDAO">

    <insert id="insertBoard">
    </insert>

    <select id="getBoard" resultType="com.demo.domain.Board">
    </select>

    <select id="getBoardList" parameterType="String" resultType="com.demo.domain.Board">
    </select>
    
    <update id="updateBoard">
    </update>
    
    <delete id="deleteBoard">
    </delete>
    
</mapper>
```
- 쿼리가 제대로 동작하는지 테스트
```
    @Autowired
    private BoardDAO boardRepo;
```

# 페이징 처리 (PagedListHolder 클래스 사용하는 방법)
- DB 쿼리 결과를 List 형태로 받고, 이를 PagedListHolder에 넣는다.
  - PAGE_SIZE : 한 페이지에 보여줄 게시글의 수
  - PAGE_CNT : pagination 갯수 (ex=4 ---> "<< < 1 2 3 4 > >>")
```
	@Autowired
	private BoardDAO boardRepo;
	private PagedListHolder<Board> pagedList;
	private static final int PAGE_SIZE = 7;
	private static final int PAGE_CNT = 4;
	
	@RequestMapping(value="/board/{category}", method=RequestMethod.GET)
	public String getBoardList(@PathVariable String category, Model model) {

		List<Board> boardList = boardRepo.getBoardList(category);
		
		pagedList = new PagedListHolder<Board>(boardList);
		pagedList.setPageSize(PAGE_SIZE);
		pagedList.setPage(0);
		
		model.addAttribute("boardList", pagedList);
		model.addAttribute("pageCnt", PAGE_CNT);
		model.addAttribute("category", category);
		
		return "board";
	}
```
- PagedListHolder 클래스 API 설명
  - https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/support/PagedListHolder.html
  - bootstrap을 이용해 구현한 부분
  - getPage의 경우 0부터 시작하기 때문에 적절하게 조절할 필요가 있다.
```
	<nav th:with="startIdx = ${boardList.getPage()/pageCnt*pageCnt},
		endIdx = ${startIdx+pageCnt-1 >= boardList.getPageCount()} ? 
			${boardList.getPageCount()-1} : ${startIdx+pageCnt-1}">
		<ul class="pagination">

			<li class="page-item">
				<a class="page-link"
					th:href="@{/board/{category}/page/{page}
						(category=${category}, page=${startIdx-pageCnt+1})}"
					th:style="${startIdx+1==1} ? 'display:none' : 'display:block'">
					<span>&laquo;</span>
			    </a>
			</li>
			
			<li class="page-item">
				<a class="page-link"
					th:href="@{/board/{category}/page/{page}
						(category=${category}, page=${boardList.getPage()})}"
					th:style="${boardList.isFirstPage()} ? 'display:none' : 'display:block'">
					<span>&lt;</span>
			    </a>
			</li>
			
			<li class="page-item" 
				th:style="${startIdx >= pageCnt*2-2} ?
					'display:block' : 'display:none'">
				<a class="page-link"
					th:href="@{/board/{category}/page/1
						(category=${category})}">
					<span>1</span>
				</a>
			</li>
			
			<li class="page-item"
				th:style="${startIdx >= pageCnt*2-2} ?
					'display:block' : 'display:none'">
				<a class="page-link">
					<span>...</span>
				</a>
			</li>
			
			<li class="page-item"
				th:each="i : ${#numbers.sequence(startIdx, endIdx)}"
				th:classappend="${boardList.getPage() == i} ? 'active' : ''">
				
				<a class="page-link"
					th:href="@{/board/{category}/page/{page}
						(category=${category}, page=${i+1})}">
					<span th:text="${i+1}"></span>
				</a>
			</li>
			
			<li class="page-item"
				th:style="${startIdx+pageCnt >= boardList.getPageCount()} ?
						'display:none' : 'display:block'">
				<a class="page-link">
					<span>...</span>
				</a>
			</li>
			
			<li class="page-item" 
				th:style="${startIdx+pageCnt >= boardList.getPageCount()} ?
						'display:none' : 'display:block'">
				<a class="page-link"
					th:href="@{/board/{category}/page/{page}
						(category=${category}, page=${boardList.getPageCount()})}">
					<span th:text="${boardList.getPageCount()}"></span>
				</a>
			</li>

			<li>
		      <a class="page-link"
		      	th:href="@{/board/{category}/page/{page}
		      		(category=${category}, page=${boardList.getPage()+2})}"
		      	th:style="${boardList.isLastPage()} ? 'display:none' : 'display:block'">
		        <span>&gt;</span>
		      </a>
		    </li>
		    
			<li class="page-item">
				<a class="page-link"
					th:href="@{/board/{category}/page/{page}
						(category=${category}, page=${endIdx+2})}"
					th:style="${startIdx+pageCnt >= boardList.getPageCount()} ?
						'display:none' : 'display:block'">
					<span>&raquo;</span>
			    </a>
			</li>
		</ul>
	</nav>
```

# 컨트롤러 파라미터 처리
- 컨트롤러 파라미터
  - PathVariable : URI 템플릿 변수에 접근할 때 사용 (GET 방식 파라미터 전달)
  - RequestParam : form 태그 내부의 name 속성에 맵핑 (POST 등의 방식 파라미터 전달)
- Pathvariable Optional Parameter
  - RequestMapping의 value값에 optional로 올 수 있는 경로들을 여러개 적는다.
  - Pathvariable에 Optional를 사용한다.
  - isPresent로 검사하고 존재한다면 get으로 데이터를 얻는다.
```
	@RequestMapping(value= {"/board/{category}/page",
			"/board/{category}/page/{page}"}, method=RequestMethod.GET)
	public String getBoardListPage(@PathVariable Optional<Integer> page,
			@PathVariable String category,
			Model model) {
		
		int resPage = page.isPresent() ? page.get() : 1;
```
- 컨트롤러 RequestMapping에 정규 표현식 사용 예제
  - 첫 번째 : board 이후 숫자가 온다.
  - 두 번째 : board 이후 알파벳이 온다.
```
@RequestMapping(value="/board/{bid:[0-9]+}", method=RequestMethod.GET)
@RequestMapping(value="/board/{category:[a-zA-Z]+}", method=RequestMethod.GET)
```
- 컨트롤러로 이동시 이전 URL 기억하는 방법
  - Controller 매개변수로 HttpServletRequest request 사용
```
model.addAttribute("oldURL", request.getHeader("referer"));

// template에서
<a th:href="@{${oldURL}}">목록으로</a>
```

- 컨트롤러 리다이렉션 전에 alert 메시지 띄우기
  - HttpServletResponse와 PrintWriter 사용
  - void 타입이기 때문에 return으로 리다이렉션 불가능
```
	@RequestMapping(value="/board/insert", method=RequestMethod.POST)
	public void insertBoard(Board b, HttpServletResponse response) 
			throws IOException {
		
		response.setContentType("text/html; charset=UTF-8");
		PrintWriter out = response.getWriter();
		out.println("<script>alert('새 글 등록 완료');");
		out.println("location.href='/board/" + b.getCategory() + "';");
		out.println("</script>");
		out.flush();
	}
```

# 인터셉터 구현 (SpringBoot)
- Controller에 데이터가 전달되기 전에 데이터를 얻고 싶은 경우 처리
- 인터셉터 클래스 구현
  - 해당 예제는 Controller에 데이터가 전달되기 전에 URL을 얻기 위해 사용
```
public class BoardInterceptor extends HandlerInterceptorAdapter {
	
	public Map pathVariables;

	@Override
	public boolean preHandle(HttpServletRequest request,
			HttpServletResponse response, Object handler) throws Exception {
	      
		pathVariables = (Map) request.getAttribute(HandlerMapping.URI_TEMPLATE_VARIABLES_ATTRIBUTE); 
		
		// 적절한 데이터 처리 ...

		request.setAttribute("pathMappings", pathVariables);
		
		return true;
	}
}
```
- 구현한 인터페이스를 등록
  - WebMvcConfig 클래스를 만든다.
  - 구현한 인터셉터에 대해 처리할 경로, 제외할 경로 등을 설정한다.
```
@Configuration
public class WebMvcConfig extends WebMvcConfigurerAdapter {
	
	  @Override
	  public void addInterceptors(InterceptorRegistry registry) {

		  registry.addInterceptor(new BoardInterceptor())
		  	.addPathPatterns("/board/ALL/page")
		  	.addPathPatterns("/board/ALL/page/*")
		  	.addPathPatterns("/board/NOTICE/page")
		  	.addPathPatterns("/board/NOTICE/page/*");
	  }
}
```
- Controller에서 인터셉터를 사용한다.
  - 컨트롤러의 매개변수로 HttpServletRequest request 를 받는다.
```
	Map pathMappings = (Map) request.getAttribute("pathMappings");
		
	(String) pathMappings.get("템플릿에서 넘어온 변수명");
```

# Thymeleaf 사용
- 컨트롤러에서 넘어온 Model 값을 얻어야 하는 경우 (javascript)
```
model.addAttribute("status","fail");

	var msg = "[[${status}]]";
	console.log(msg)
```
- input 안에 데이터가 존재해야 하는 경우
```
<input ... th:required="required">
```
- 글자 수 Not null 등 제한
  - Domain 클래스에서 어노테이션 사용 (mybatis, jpa 상관없이 사용 가능)
  - 어노테이션 정리 : http://wiki.gurubee.net/pages/viewpage.action?pageId=12189867
  - 여기서 Size 예제는 바이트 수가 아닌 글자수 제한이다.
  - 즉, 영어도 50글자 한글도 50글자 제한
```
public class Board {
	private long bid;
	
	@Size(max=50, message="50글자 제약조건")
	private String title;
```
- POST를 처리하는 Controller에서 Valid 어노테이션과 BindingResult를 사용
  - POST 전에 GET 방식에서 빈 Board 객체를 넘겨 주어야 한다 (넘기지 않을 시 나중에 에러 발생)
  - form 적용시 th:object를 이용해 GET에서 넘겨준 board 사용
```
	@RequestMapping(value="/board/insert", method=RequestMethod.GET)
	public String insertBoard(HttpServletRequest request,
			Model model) {
		
		Board b = new Board();
		
		model.addAttribute("board",b);

		return "boardInsert";
	}

// thymeleaf
<form th:action="@{/board/insert}" th:object="${board}" method="post">
```
```
// 매개변수로 BindingResult 사용

	@RequestMapping(value="/board/insert", method=RequestMethod.POST)
	public String insertBoard(@Valid Board b, 
			BindingResult bindingResult,
			Model model) {
		
	    if (bindingResult.hasErrors()) {
	    	model.addAttribute("status","fail");
	    	model.addAttribute("board", b);
	    	return "boardInsert";
	    }
	    
	    boardRepo.insertBoard(b);
	    return "redirect:/board/" + b.getCategory();
	}
```
- Thymeleaf에서 Domain 클래스의 어노테이션에 등록한 message 띄우기
  - BindingResult와 th:object로 인해 fields 사용 가능
  - 이후 help-block 클래스 커스터마이징
  - th:errors로 인해 message값이 span 태그의 텍스트로 들어간다.
```
	<span th:if="${#fields.hasErrors('title')}"
		class="help-block" th:errors="*{title}"></span>
```

# Spring Security
- Springboot Maven 사용
```
		<dependency>
		    <groupId>org.springframework.boot</groupId>
		    <artifactId>spring-boot-starter-security</artifactId>
		</dependency>
		<dependency>
		    <groupId>org.thymeleaf.extras</groupId>
		    <artifactId>thymeleaf-extras-springsecurity5</artifactId>
		</dependency>
```
- Security 관련 설정 클래스 파일 만들기
  - 일단 기본으로 모든 경로에 인증 허가를 설정
```
@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

	@Override
	public void configure(AuthenticationManagerBuilder auth) throws Exception {

	}

	@Override
	public void configure(HttpSecurity http) throws Exception {
		http.authorizeRequests().antMatchers("/**").permitAll();
	}
}
```
- Thymeleaf에서 csrf 토큰 사용 예제
  - form 태그 안에 input type hidden으로 csrf 토큰을 생성한다.
  - 개발자 모드에서 토큰이 제대로 생성되는지 확인한다.
  - 만약 form 태그에 th:action을 사용한다면 해당 부분을 적어주지 않더라도 csrf 토큰이 자동으로 생성된다.
```
<form>
	...
		<input type="hidden" th:name="${_csrf.parameterName}"
			th:value="${_csrf.token}"/>
		<input type="submit" value="완료" class="btn btn-primary">
</form>
```
- Thymeleaf의 Ajax에서 csrf 토큰 사용 예제
  - csrf.token과 csrf.headerName이 필요
  - beforeSend로 헤더에 토큰값을 셋팅한다.
```
	$('.cmt_btn').click(() => {
		
		var replData = {
			content: $('.write_inp').val(),
			writer: 'user00',
			fbid: [[${board.getBid()}]],
			csrfToken: '[[${_csrf.token}]]',
			csrfHeader: '[[${_csrf.headerName}]]'
		};

		$.ajax({
			type: "post",
			url: '/board/replies/insert',
			data: JSON.stringify(replData),
			dataType: 'json',
			beforeSend: function(xhr){
				xhr.setRequestHeader(replData.csrfHeader, replData.csrfToken);
			},
			contentType: "application/json; charset=UTF-8",
		})
		.done(reply => {
			console.log(reply);
		})
		
	});
```
- Ajax 사용시 Controller에서는 RequestBody로 데이터를 얻고, ResponseEntity를 반환한다.
  - ResponseEntity 안의 데이터 타입은 Ajax 결과 후 새로 그리기 위해 이후에 List 형태 등으로 지정
```
// ex) ResponseEntity<List<Replies>>

	@RequestMapping(value="/board/replies/insert", method=RequestMethod.POST)
	public ResponseEntity<Map> insertReplies(@RequestBody Replies r) {
		System.out.println(replData);
		Map<String, String> returnData = new HashMap<>();
		returnData.put("status", "success");
		
		return new ResponseEntity<>(returnData, HttpStatus.ACCEPTED);
	}
```