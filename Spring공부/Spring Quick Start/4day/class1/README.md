# 어노테이션 기반 MVC
- MVC 설정파일(action-servlet.xml)의 namespaces에서 context를 추가
- context-component-scan 엘리먼트 사용
```
	<context:component-scan base-package="com.springbook.view">
	</context:component-scan>
```
- Controller 사용하기
  - 기존의 import Controller와 implements Controller를 삭제하고, 어노테이션을 사용한다.
  - 또한 ModelAndView handleRequest() 메소드도 삭제한다.
  - ModelAndView를 리턴하는 화면 네비게이션 부분도 삭제한다.
```
import org.springframework.stereotype.Controller;

@Controller
public class InsertBoardController {
	public void insertBoard(HttpServletRequest request) {
		System.out.println("글 등록 처리");
		...
	}
}
```
- RequestMapping 사용하기
  - 기존의 HandlerMapping의 설정을 대체한다.
  - insertBoard.do 에 대한 요청이 들어오면 insertBoard() 메소드를 수행한다.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public void insertBoard(HttpServletRequest request) {
		System.out.println("글 등록 처리");
		...
	}
}
```
# Command 객체 이용하기
- 기존의 insertBoard를 살펴보면 request.getParameter를 이용하여 사용자의 요청 정보를 읽어오고, 이를 vo에 셋팅한 후 insertBoard를 수행한다.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public void insertBoard(HttpServletRequest request) {
		System.out.println("글 등록 처리");
		
		// 1. 사용자 입력 정보 추출
		// request.setCharacterEncoding("EUC-KR");
		String title = request.getParameter("title");
		String writer = request.getParameter("writer");
		String content = request.getParameter("content");
		
		// 2. DB 연동 처리
		BoardVO vo = new BoardVO();
		vo.setTitle(title);
		vo.setWriter(writer);
		vo.setContent(content);
		
		BoardDAO boardDAO = new BoardDAO();
		boardDAO.insertBoard(vo);
		
	}

}
```
- 하지만 사용자의 입력이 변화하면 소스코드 또한 매번 변경해 주어야 하고, 길어지기도 한다.
- 이를 해결하기 위해 Command 객체를 이용한다.
```
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class InsertBoardController {
	
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo, BoardDAO boardDAO) {
		System.out.println("글 등록 처리");
		
		boardDAO.insertBoard(vo);
		// return "getBoardList.do"; ---> 포워드 방식(URL이 변경되지 않음)
		return "redirect:getBoardList.do";
	}

}

```
- 기존의 vo로 셋팅하는 부분을 모두 삭제하고 단순히 insertBoard를 수행한다.
- 동작 방식은 다음과 같다.
- 클라이언트의 요청이 오면 HttpServletRequest 객체의 service() 메소드를 호출하며, 클라이언트 파라미터를 인자로 전달해준다.
- 스프링 컨테이너는 insertBoard의 매개변수인 BoardVO 객체를 생성하고, 클라이언트 요청에 해당하는 Setter 메소드들을 자동으로 호출한다.
- BoardVO 객체에 Setter를 이용한 저장이 완료되면 사용자 입력값들이 설정된 BoardVO 객체가 인자로 전달된다.
- BoardDAO 또한 동일하게 동작한다.