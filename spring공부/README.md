# Springboot ��� ���̺귯�� (���̺�)
- DevTools
- Lombok
- MyBatis
- Thymeleaf
- Web
- PostgreSQL

# PostgreSQL ��ġ �� ����
- ��ġ
  - https://www.tutorialspoint.com/postgresql/postgresql_environment.htm
- �ѱ� ó��
```
set server_encoding = 'UTF8';
set client_encoding = 'UTF8';
CREATE DATABASE [[��� �̸�]] TEMPLATE template0 LC_COLLATE 'C';
```

- ����� �÷� Ÿ�� ����
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
- �ش� �����ͺ��̽��� �������� DTO Ŭ���� ���� �ۼ�
  - lombok���� getter, setter �޼ҵ带 ��������� ���� ���
  - Maven Dependencies���� lombok.jar�� ��ġ�Ǿ� �ִ� ��η� �̵� �� jar ���� ����
  - C:\Users\lih\.m2\repository\org\projectlombok\lombok\1.18.6
  - eclipse.exe����, lombok ��ġ �� ��Ŭ���� �����
```
@Data
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Board {
```

# SpringBoot PostgreSQL Mybatis ����
- src/main/resources/application.properties ���Ͽ� dataSource ���
```
spring.datasource.driver-class-name=org.postgresql.Driver
spring.datasource.url=jdbc:postgresql://localhost:5432/postgres
spring.datasource.username=postgres
spring.datasource.password=1234
```
- SpringBootApplication Ŭ���� ���Ͽ���
  - ���߿� DAO �������̽��� Autowired �ϱ� ���� MapperScan�� ���
  - SqlSessionFactory�� �̿��� Mapper.xml ���� �ε�
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
- DTO Ŭ������ �������� DAO �������̽� ����
  - mybatis�� ����� ��� : Mapper ������̼� ���
```
@Mapper
public interface BoardDAO {

	public void insertBoard(Board b);
```
- Mybatis�� �̿��� xml ���� �ۼ�
  - resources ���� �Ʒ� mappers ���� ���� �� xml ���� �ۼ�
  - mapper namespace : ������ ������ �������̽��� ��θ� �����ش�.
  - id : �����ϰ��� �ϴ� �޼ҵ� ���� �����ش�.
  - resultType : ��ȯ�� Ÿ���� Ŭ���� ��θ� �����ش�.
  - parameterType : �Ű������� ���� Ÿ���� ����
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
- ������ ����� �����ϴ��� �׽�Ʈ
```
    @Autowired
    private BoardDAO boardRepo;
```

# ����¡ ó�� (PagedListHolder Ŭ���� ����ϴ� ���)
- DB ���� ����� List ���·� �ް�, �̸� PagedListHolder�� �ִ´�.
  - PAGE_SIZE : �� �������� ������ �Խñ��� ��
  - PAGE_CNT : pagination ���� (ex=4 ---> "<< < 1 2 3 4 > >>")
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
- PagedListHolder Ŭ���� API ����
  - https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/support/PagedListHolder.html
  - bootstrap�� �̿��� ������ �κ�
  - getPage�� ��� 0���� �����ϱ� ������ �����ϰ� ������ �ʿ䰡 �ִ�.
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

# ��Ʈ�ѷ� �Ķ���� ó��
- ��Ʈ�ѷ� �Ķ����
  - PathVariable : URI ���ø� ������ ������ �� ��� (GET ��� �Ķ���� ����)
  - RequestParam : form �±� ������ name �Ӽ��� ���� (POST ���� ��� �Ķ���� ����)
- Pathvariable Optional Parameter
  - RequestMapping�� value���� optional�� �� �� �ִ� ��ε��� ������ ���´�.
  - Pathvariable�� Optional�� ����Ѵ�.
  - isPresent�� �˻��ϰ� �����Ѵٸ� get���� �����͸� ��´�.
```
	@RequestMapping(value= {"/board/{category}/page",
			"/board/{category}/page/{page}"}, method=RequestMethod.GET)
	public String getBoardListPage(@PathVariable Optional<Integer> page,
			@PathVariable String category,
			Model model) {
		
		int resPage = page.isPresent() ? page.get() : 1;
```
- ��Ʈ�ѷ� RequestMapping�� ���� ǥ���� ��� ����
  - ù ��° : board ���� ���ڰ� �´�.
  - �� ��° : board ���� ���ĺ��� �´�.
```
@RequestMapping(value="/board/{bid:[0-9]+}", method=RequestMethod.GET)
@RequestMapping(value="/board/{category:[a-zA-Z]+}", method=RequestMethod.GET)
```
- ��Ʈ�ѷ��� �̵��� ���� URL ����ϴ� ���
  - Controller �Ű������� HttpServletRequest request ���
```
model.addAttribute("oldURL", request.getHeader("referer"));

// template����
<a th:href="@{${oldURL}}">�������</a>
```

- ��Ʈ�ѷ� �����̷��� ���� alert �޽��� ����
  - HttpServletResponse�� PrintWriter ���
  - void Ÿ���̱� ������ return���� �����̷��� �Ұ���
```
	@RequestMapping(value="/board/insert", method=RequestMethod.POST)
	public void insertBoard(Board b, HttpServletResponse response) 
			throws IOException {
		
		response.setContentType("text/html; charset=UTF-8");
		PrintWriter out = response.getWriter();
		out.println("<script>alert('�� �� ��� �Ϸ�');");
		out.println("location.href='/board/" + b.getCategory() + "';");
		out.println("</script>");
		out.flush();
	}
```

# ���ͼ��� ���� (SpringBoot)
- Controller�� �����Ͱ� ���޵Ǳ� ���� �����͸� ��� ���� ��� ó��
- ���ͼ��� Ŭ���� ����
  - �ش� ������ Controller�� �����Ͱ� ���޵Ǳ� ���� URL�� ��� ���� ���
```
public class BoardInterceptor extends HandlerInterceptorAdapter {
	
	public Map pathVariables;

	@Override
	public boolean preHandle(HttpServletRequest request,
			HttpServletResponse response, Object handler) throws Exception {
	      
		pathVariables = (Map) request.getAttribute(HandlerMapping.URI_TEMPLATE_VARIABLES_ATTRIBUTE); 
		
		// ������ ������ ó�� ...

		request.setAttribute("pathMappings", pathVariables);
		
		return true;
	}
}
```
- ������ �������̽��� ���
  - WebMvcConfig Ŭ������ �����.
  - ������ ���ͼ��Ϳ� ���� ó���� ���, ������ ��� ���� �����Ѵ�.
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
- Controller���� ���ͼ��͸� ����Ѵ�.
  - ��Ʈ�ѷ��� �Ű������� HttpServletRequest request �� �޴´�.
```
	Map pathMappings = (Map) request.getAttribute("pathMappings");
		
	(String) pathMappings.get("���ø����� �Ѿ�� ������");
```

# Thymeleaf ���
- ��Ʈ�ѷ����� �Ѿ�� Model ���� ���� �ϴ� ��� (javascript)
```
model.addAttribute("status","fail");

	var msg = "[[${status}]]";
	console.log(msg)
```
- input �ȿ� �����Ͱ� �����ؾ� �ϴ� ���
```
<input ... th:required="required">
```
- ���� �� Not null �� ����
  - Domain Ŭ�������� ������̼� ��� (mybatis, jpa ������� ��� ����)
  - ������̼� ���� : http://wiki.gurubee.net/pages/viewpage.action?pageId=12189867
  - ���⼭ Size ������ ����Ʈ ���� �ƴ� ���ڼ� �����̴�.
  - ��, ��� 50���� �ѱ۵� 50���� ����
```
public class Board {
	private long bid;
	
	@Size(max=50, message="50���� ��������")
	private String title;
```
- POST�� ó���ϴ� Controller���� Valid ������̼ǰ� BindingResult�� ���
  - POST ���� GET ��Ŀ��� �� Board ��ü�� �Ѱ� �־�� �Ѵ� (�ѱ��� ���� �� ���߿� ���� �߻�)
  - form ����� th:object�� �̿��� GET���� �Ѱ��� board ���
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
// �Ű������� BindingResult ���

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
- Thymeleaf���� Domain Ŭ������ ������̼ǿ� ����� message ����
  - BindingResult�� th:object�� ���� fields ��� ����
  - ���� help-block Ŭ���� Ŀ���͸���¡
  - th:errors�� ���� message���� span �±��� �ؽ�Ʈ�� ����.
```
	<span th:if="${#fields.hasErrors('title')}"
		class="help-block" th:errors="*{title}"></span>
```

# Spring Security
- Springboot Maven ���
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
- Security ���� ���� Ŭ���� ���� �����
  - �ϴ� �⺻���� ��� ��ο� ���� �㰡�� ����
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
- Thymeleaf���� csrf ��ū ��� ����
  - form �±� �ȿ� input type hidden���� csrf ��ū�� �����Ѵ�.
  - ������ ��忡�� ��ū�� ����� �����Ǵ��� Ȯ���Ѵ�.
  - ���� form �±׿� th:action�� ����Ѵٸ� �ش� �κ��� �������� �ʴ��� csrf ��ū�� �ڵ����� �����ȴ�.
```
<form>
	...
		<input type="hidden" th:name="${_csrf.parameterName}"
			th:value="${_csrf.token}"/>
		<input type="submit" value="�Ϸ�" class="btn btn-primary">
</form>
```
- Thymeleaf�� Ajax���� csrf ��ū ��� ����
  - csrf.token�� csrf.headerName�� �ʿ�
  - beforeSend�� ����� ��ū���� �����Ѵ�.
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
- Ajax ���� Controller������ RequestBody�� �����͸� ���, ResponseEntity�� ��ȯ�Ѵ�.
  - ResponseEntity ���� ������ Ÿ���� Ajax ��� �� ���� �׸��� ���� ���Ŀ� List ���� ������ ����
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