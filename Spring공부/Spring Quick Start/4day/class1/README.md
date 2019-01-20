# ������̼� ��� MVC
- MVC ��������(action-servlet.xml)�� namespaces���� context�� �߰�
- context-component-scan ������Ʈ ���
```
	<context:component-scan base-package="com.springbook.view">
	</context:component-scan>
```
- Controller ����ϱ�
  - ������ import Controller�� implements Controller�� �����ϰ�, ������̼��� ����Ѵ�.
  - ���� ModelAndView handleRequest() �޼ҵ嵵 �����Ѵ�.
  - ModelAndView�� �����ϴ� ȭ�� �׺���̼� �κе� �����Ѵ�.
```
import org.springframework.stereotype.Controller;

@Controller
public class InsertBoardController {
	public void insertBoard(HttpServletRequest request) {
		System.out.println("�� ��� ó��");
		...
	}
}
```
- RequestMapping ����ϱ�
  - ������ HandlerMapping�� ������ ��ü�Ѵ�.
  - insertBoard.do �� ���� ��û�� ������ insertBoard() �޼ҵ带 �����Ѵ�.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public void insertBoard(HttpServletRequest request) {
		System.out.println("�� ��� ó��");
		...
	}
}
```
# Command ��ü �̿��ϱ�
- ������ insertBoard�� ���캸�� request.getParameter�� �̿��Ͽ� ������� ��û ������ �о����, �̸� vo�� ������ �� insertBoard�� �����Ѵ�.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public void insertBoard(HttpServletRequest request) {
		System.out.println("�� ��� ó��");
		
		// 1. ����� �Է� ���� ����
		// request.setCharacterEncoding("EUC-KR");
		String title = request.getParameter("title");
		String writer = request.getParameter("writer");
		String content = request.getParameter("content");
		
		// 2. DB ���� ó��
		BoardVO vo = new BoardVO();
		vo.setTitle(title);
		vo.setWriter(writer);
		vo.setContent(content);
		
		BoardDAO boardDAO = new BoardDAO();
		boardDAO.insertBoard(vo);
		
	}

}
```
- ������ ������� �Է��� ��ȭ�ϸ� �ҽ��ڵ� ���� �Ź� ������ �־�� �ϰ�, ������⵵ �Ѵ�.
- �̸� �ذ��ϱ� ���� Command ��ü�� �̿��Ѵ�.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo, BoardDAO boardDAO) {
		System.out.println("�� ��� ó��");
		
		boardDAO.insertBoard(vo);
		// return "getBoardList.do"; ---> ������ ���(URL�� ������� ����)
		return "redirect:getBoardList.do";
	}

}

```
- ������ vo�� �����ϴ� �κ��� ��� �����ϰ� �ܼ��� insertBoard�� �����Ѵ�.
- ���� ����� ������ ����.
- Ŭ���̾�Ʈ�� ��û�� ���� HttpServletRequest ��ü�� service() �޼ҵ带 ȣ���ϸ�, Ŭ���̾�Ʈ �Ķ���͸� ���ڷ� �������ش�.
- ������ �����̳ʴ� insertBoard�� �Ű������� BoardVO ��ü�� �����ϰ�, Ŭ���̾�Ʈ ��û�� �ش��ϴ� Setter �޼ҵ���� �ڵ����� ȣ���Ѵ�.
- BoardVO ��ü�� Setter�� �̿��� ������ �Ϸ�Ǹ� ����� �Է°����� ������ BoardVO ��ü�� ���ڷ� ���޵ȴ�.
- BoardDAO ���� �����ϰ� �����Ѵ�.