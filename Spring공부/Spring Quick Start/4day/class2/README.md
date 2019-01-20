# 컨트롤러 통합
```
import org.springframework.web.servlet.ModelAndView;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class GetBoardListController {

	@RequestMapping("/getBoardList.do")
	public ModelAndView getBoardList(BoardVO vo, BoardDAO boardDAO, ModelAndView mav) {
		System.out.println("글 목록 검색 처리");
		
		mav.addObject("boardList",boardDAO.getBoardList(vo));
		mav.setViewName("getBoardList.jsp");
		return mav;
	}
}
```
- Model 정보를 저장하여 넘겨주기 위해서 String 타입을 return 하는것이 아닌 ModelAndView 타입을 리턴한다.
  - addObject와 setViewName으로 ModelAndView 셋팅 후 리턴한다.
- 어노테이션을 사용하면서 소스코드가 매우 짧아졌기 때문에 하나의 Controller로 통합할 수도 있다.
```
@Controller
public class BoardController {
	// 글 등록
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo, BoardDAO boardDAO) {}

	// 글 수정
	@RequestMapping("/updateBoard.do")
	public String updateBoard(BoardVO vo, BoardDAO boardDAO) {}

	// 글 삭제
	@RequestMapping("/deleteBoard.do")
	public String deleteBoard(BoardVO vo, BoardDAO boardDAO) {}

	...
}
```
- RequestMapping 어노테이션의 경우 Post와 Get 두 개를 설정할 수 있음
  - @RequestMapping("/login.do", method=RequestMethod.GET)
  - @RequestMapping("/login.do", method=RequestMethod.POST)

# Model 객체 사용
- 컨트롤러에서 ModelAndView 타입이 아닌 String 타입으로 리턴을 통일하고 싶은 경우
  - Model 객체를 사용해 정보를 담을 수 있다.
```
import org.springframework.ui.Model;

public String getBoard(BoardVO vo, BoardDAO boardDAO, Model model){
	model.addAttribute("board", boardDAO.getBoard(vo));
	return "getBoard.jsp";
}
```

# Session 사용
- HttpSession 객체 사용
  - java에서 jsp로 넘어갈 때 session에 정보를 담아서 다음 jsp에서 사용
```
import javax.servlet.http.HttpSession;

public String login(UserVO vo, UserDAO userDAO, HttpSession session) {
	session.setAttribute("userName", user.getName());
}

jsp에서 사용 : ${userName}
```

# Session을 이용해 Null값 세션으로 업데이트
- 업데이트 시 Null값을 세션에 저장된 값으로 업데이트
  - SessionAttributes와 ModelAttribute 어노테이션 사용
```
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.bind.annotation.ModelAttribute;

@Controller
@SessionAttributes("board")
public class BoardController {
	// 글 수정
	@RequestMapping("/updateBoard.do")
	public String updateBoard(@ModelAttribute("board") BoardVO vo, BoardDAO boardDAO) {
	...
	}
}
- 동작 방식을 살펴보면 다음과 같다.
- 이전에 구현했던 getBoard() 메소드를 살펴보면 Model에 정보를 담는다.
```
public String getBoard(BoardVO vo, BoardDAO boardDAO, Model model){
	model.addAttribute("board", boardDAO.getBoard(vo));
	return "getBoard.jsp";
}
```
- SessionAttributes 어노테이션 설정을 통해 Model에 "board"라는 이름을 세션에 자동으로 저장하도록 설정한다.
```
@SessionAttributes("board")
```
- updateBoard() 메소드 호출 시 ModelAttribute 어노테이션 설정을 통해 세션에 "board"라는 이름으로 저장된 데이터가 있는지 확인한다.
  - 데이터가 있다면 세션에서 정보를 꺼내 선언된 vo 변수에 할당한다.
- 사용자가 만약 title과 content만 입력했다면, 입력하지 않은 나머지 정보들은 세션에 저장된 데이터로 지정한다.
```
	public String updateBoard(@ModelAttribute("board") BoardVO vo, BoardDAO boardDAO) {
	...
	}
```