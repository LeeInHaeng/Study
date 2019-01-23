# Controller�� DAO ��ü�� ���� �̿��ϸ� �ȵǴ� ����1 : ��������
- �������� �������� DAO Ŭ������ �ٸ� Ŭ������ ���� ��ü�ϱ� ���ؼ�
- DAO�� ���� ����ϴ� Controller�� ������ �����Ѵٸ�, DAO ���� �� Controller�� ������ �� ������ �־�� �Ѵ�.
- �̷��� ���� �ذ��� ���� Controller�� Service �������̽��� �̿��ϰ�, ���� DAO�� ����Ǵ��� ������ ������ �Ѵ�.
```
// ���� DAO�� ���� ����ϴ� �ڵ�
@Controller
@SessionAttributes("board")
public class BoardController {
	@Autowired
	private BoardDAOSpring boardDAO;
	
	// �� ���
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) {
		System.out.println("�� ��� ó��");
		
		boardDAO.insertBoard(vo);
		// return "getBoardList.do"; ---> ������ ���(URL�� ������� ����)
		return "redirect:getBoardList.do";
	}
	...
}

// DAO�� ���� ������� �ʰ� Service �������̽��� ����ϴ� �ڵ�
@Controller
@SessionAttributes("board")
public class BoardController {
	@Autowired
	private BoardService boardService;
	
	// �� ���
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) {
		System.out.println("�� ��� ó��");
		
		boardService.insertBoard(vo);
		// return "getBoardList.do"; ---> ������ ���(URL�� ������� ����)
		return "redirect:getBoardList.do";
	}
	...
}

// BoardServiceImpl.java
@Service("boardService")
public class BoardServiceImpl implements BoardService{
	@Autowired
	private BoardDAOSpring boardDAO; ----> DAO ����� �� �κи� ������ �ָ� ���������� ������
	...
}
```

# Controller�� DAO ��ü�� ���� �̿��ϸ� �ȵǴ� ����1 : AOP ���� ����
- �׵��� ������ ����Ʈ���� Service ����Ŭ����(*.Impl)�� �����ϵ��� ������ �Ǿ��ִ�.
- �̸� ���� DAO�� ���� �����ϴ� ���� �ƴ� Sservice�� �̿��Ѵ�.

# 2-Layered ��Ű����
![996c083359bf82c028](https://user-images.githubusercontent.com/20277647/51588403-6fb79a80-1f27-11e9-9f18-838ceb3a33ef.png)
- web.xml �������� action-servlet.xml ���ϸ� �б� ������ applicationContext.xml ���� ������ ���� ���Ѵ�.
- Controller ��ü�� �����Ǳ� ���� applicationContext.xml ������ �о� ����Ͻ� ������Ʈ���� �޸𸮿� �����ؾ��Ѵ�.
- �̸� ���� ContextLoaderListener�� ����Ѵ�.
- �ܼ��� web.xml�� ContextLoaderListener�� ����ϸ� action-servlet.xml ���� applicationContext.xml�� ���� �� �ִ�.
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