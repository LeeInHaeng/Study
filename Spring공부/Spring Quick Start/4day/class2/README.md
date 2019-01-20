# ��Ʈ�ѷ� ����
```
import org.springframework.web.servlet.ModelAndView;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class GetBoardListController {

	@RequestMapping("/getBoardList.do")
	public ModelAndView getBoardList(BoardVO vo, BoardDAO boardDAO, ModelAndView mav) {
		System.out.println("�� ��� �˻� ó��");
		
		mav.addObject("boardList",boardDAO.getBoardList(vo));
		mav.setViewName("getBoardList.jsp");
		return mav;
	}
}
```
- Model ������ �����Ͽ� �Ѱ��ֱ� ���ؼ� String Ÿ���� return �ϴ°��� �ƴ� ModelAndView Ÿ���� �����Ѵ�.
  - addObject�� setViewName���� ModelAndView ���� �� �����Ѵ�.
- ������̼��� ����ϸ鼭 �ҽ��ڵ尡 �ſ� ª������ ������ �ϳ��� Controller�� ������ ���� �ִ�.
```
@Controller
public class BoardController {
	// �� ���
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo, BoardDAO boardDAO) {}

	// �� ����
	@RequestMapping("/updateBoard.do")
	public String updateBoard(BoardVO vo, BoardDAO boardDAO) {}

	// �� ����
	@RequestMapping("/deleteBoard.do")
	public String deleteBoard(BoardVO vo, BoardDAO boardDAO) {}

	...
}
```
- RequestMapping ������̼��� ��� Post�� Get �� ���� ������ �� ����
  - @RequestMapping("/login.do", method=RequestMethod.GET)
  - @RequestMapping("/login.do", method=RequestMethod.POST)

# Model ��ü ���
- ��Ʈ�ѷ����� ModelAndView Ÿ���� �ƴ� String Ÿ������ ������ �����ϰ� ���� ���
  - Model ��ü�� ����� ������ ���� �� �ִ�.
```
import org.springframework.ui.Model;

public String getBoard(BoardVO vo, BoardDAO boardDAO, Model model){
	model.addAttribute("board", boardDAO.getBoard(vo));
	return "getBoard.jsp";
}
```

# Session ���
- HttpSession ��ü ���
  - java���� jsp�� �Ѿ �� session�� ������ ��Ƽ� ���� jsp���� ���
```
import javax.servlet.http.HttpSession;

public String login(UserVO vo, UserDAO userDAO, HttpSession session) {
	session.setAttribute("userName", user.getName());
}

jsp���� ��� : ${userName}
```

# Session�� �̿��� Null�� �������� ������Ʈ
- ������Ʈ �� Null���� ���ǿ� ����� ������ ������Ʈ
  - SessionAttributes�� ModelAttribute ������̼� ���
```
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.bind.annotation.ModelAttribute;

@Controller
@SessionAttributes("board")
public class BoardController {
	// �� ����
	@RequestMapping("/updateBoard.do")
	public String updateBoard(@ModelAttribute("board") BoardVO vo, BoardDAO boardDAO) {
	...
	}
}
- ���� ����� ���캸�� ������ ����.
- ������ �����ߴ� getBoard() �޼ҵ带 ���캸�� Model�� ������ ��´�.
```
public String getBoard(BoardVO vo, BoardDAO boardDAO, Model model){
	model.addAttribute("board", boardDAO.getBoard(vo));
	return "getBoard.jsp";
}
```
- SessionAttributes ������̼� ������ ���� Model�� "board"��� �̸��� ���ǿ� �ڵ����� �����ϵ��� �����Ѵ�.
```
@SessionAttributes("board")
```
- updateBoard() �޼ҵ� ȣ�� �� ModelAttribute ������̼� ������ ���� ���ǿ� "board"��� �̸����� ����� �����Ͱ� �ִ��� Ȯ���Ѵ�.
  - �����Ͱ� �ִٸ� ���ǿ��� ������ ���� ����� vo ������ �Ҵ��Ѵ�.
- ����ڰ� ���� title�� content�� �Է��ߴٸ�, �Է����� ���� ������ �������� ���ǿ� ����� �����ͷ� �����Ѵ�.
```
	public String updateBoard(@ModelAttribute("board") BoardVO vo, BoardDAO boardDAO) {
	...
	}
```