# Controller가 DAO 객체를 직접 이용하면 안되는 이유1 : 유지보수
- 유지보수 과정에서 DAO 클래스를 다른 클래스로 쉽게 교체하기 위해서
- DAO를 직접 사용하는 Controller가 여러개 존재한다면, DAO 변경 시 Controller를 일일이 다 수정해 주어야 한다.
- 이러한 문제 해결을 위해 Controller는 Service 인터페이스를 이용하고, 만약 DAO가 변경되더라도 영향이 없도록 한다.
```
// 이전 DAO를 직접 사용하는 코드
@Controller
@SessionAttributes("board")
public class BoardController {
	@Autowired
	private BoardDAOSpring boardDAO;
	
	// 글 등록
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) {
		System.out.println("글 등록 처리");
		
		boardDAO.insertBoard(vo);
		// return "getBoardList.do"; ---> 포워드 방식(URL이 변경되지 않음)
		return "redirect:getBoardList.do";
	}
	...
}

// DAO를 직접 사용하지 않고 Service 인터페이스를 사용하는 코드
@Controller
@SessionAttributes("board")
public class BoardController {
	@Autowired
	private BoardService boardService;
	
	// 글 등록
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) {
		System.out.println("글 등록 처리");
		
		boardService.insertBoard(vo);
		// return "getBoardList.do"; ---> 포워드 방식(URL이 변경되지 않음)
		return "redirect:getBoardList.do";
	}
	...
}

// BoardServiceImpl.java
@Service("boardService")
public class BoardServiceImpl implements BoardService{
	@Autowired
	private BoardDAOSpring boardDAO; ----> DAO 변경시 이 부분만 변경해 주면 유지보수가 쉬워짐
	...
}
```

# Controller가 DAO 객체를 직접 이용하면 안되는 이유1 : AOP 설정 적용
- 그동안 설정한 포인트컷은 Service 구현클래스(*.Impl)에 동작하도록 설정이 되어있다.
- 이를 위해 DAO에 직접 접근하는 것이 아닌 Sservice를 이용한다.

# 2-Layered 아키텍쳐
![996c083359bf82c028](https://user-images.githubusercontent.com/20277647/51588403-6fb79a80-1f27-11e9-9f18-838ceb3a33ef.png)
- web.xml 설정에서 action-servlet.xml 파일만 읽기 때문에 applicationContext.xml 설정 파일은 읽지 못한다.
- Controller 객체가 생성되기 전에 applicationContext.xml 파일을 읽어 비즈니스 컴포넌트들을 메모리에 생성해야한다.
- 이를 위해 ContextLoaderListener를 등록한다.
- 단순히 web.xml에 ContextLoaderListener를 등록하면 action-servlet.xml 전에 applicationContext.xml을 읽을 수 있다.
```
  <context-param>
  	<param-name>contextConfigLocation</param-name>
  	<param-value>classpath:applicationContext.xml</param-value>
  </context-param>
  
  <listener>
  	<listener-class>
  		org.springframework.web.context.ContextLoaderListener
  	</listener-class>
  </listener>
```