# MVC 프레임워크 개발
- 하나의 서블릿 클래스에 모든 요청을 처리하기에는 코드가 복잡해진다.
- 최종적으로 Spring MVC를 이용할 것이지만, Spring MVC는 복잡하기 때문에 비슷한 동작을 하도록 직접 구현해본다.
- 구현할 클래스
  - DispatcherServlet : 유일한 서블릿 클래스로서 모든 클라이언트의 요청을 가장 먼저 처리하는 Front Controller
  - HandlerMapping : 클라이언트의 요청을 처리할 Controller 매핑
  - Controller : 실질적인 클라이언트의 요청 처리
  - ViewResolver : Controller가 리턴한 View 이름으로 실행될 JSP 경로 완성
- 클라이언트의 요청을 받은 DispatcherServlet은 HandlerMapping을 통해 Controller 객체를 검색하고, 검색된 Controller를 실행

# Controller 구현
- 어떤 Controller 객체가 검색되더라도 같은 코드로 실행하기 위해 Controller의 최상위 인터페이스를 구현
```
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public interface Controller {
	String handleRequest(HttpServletRequest request, HttpServletResponse response);
}
```
- 최상위 인터페이스를 이용해 컨트롤러 구현
```
public class LoginController implements Controller {
	@Override
	public String handleRequest(HttpServletRequest request, HttpServletResponse response) {
		System.out.println("로그인 처리");
		...
		return "getBoardList.do";
		혹은
		return "login"; // login.jsp가 아닌 login
	}
}
```

# HandlerMapping 클래스 구현
- 모든 Controller 객체들을 저장하고 있다가, 클라이언트의 요청이 들어오면 요청을 처리할 특정 Controller를 검색하는 기능을 제공
```
import java.util.HashMap;
import java.util.Map;

import com.springbook.view.user.LoginController;

public class HandlerMapping {
	private Map<String, Controller> mappings;
	
	public HandlerMapping() {
		mappings = new HashMap<String, Controller>();
		mappings.put("/login.do", new LoginController());
	}
	
	public Controller getController(String path) {
		return mappings.get(path);
	}
}

```

# ViewResolver 클래스 구현
- Controller가 리턴한 View 이름에 접두사, 접미사를 결합하여 최종으로 실행될 View 경로와 파일명을 완성
```

public class ViewResolver {
	public String prefix;
	public String suffix;
	
	public void setPrefix(String prefix) {
		this.prefix = prefix;
	}
	
	public void setSuffix(String suffix) {
		this.suffix = suffix;
	}
	
	public String getView(String viewName) {
		return prefix + viewName + suffix;
	}
}
```
# DispatcherServlet 수정
```
	private HandlerMapping handlerMapping;
	private ViewResolver viewResolver;
	
	public void init() throws ServletException{
		handlerMapping = new HandlerMapping();
		viewResolver = new ViewResolver();
		viewResolver.setPrefix("./");
		viewResolver.setSuffix(".jsp");
	}

	private void process(HttpServletRequest request, HttpServletResponse response) throws IOException{
		// 1. 클라이언트의 요청 path 정보를 추출
		String uri = request.getRequestURI();
		String path = uri.substring(uri.lastIndexOf("/"));
		
		// 2. HandlerMapping을 통해 path에 해당하는 Controller를 검색한다.
		Controller ctrl = handlerMapping.getController(path);
		
		// 3. 검색된 Controller를 실행한다.
		String viewName = ctrl.handleRequest(request, response);
		
		// 4. ViewResolver를 통해 viewName에 해당하는 화면을 검색한다.
		String view = null;
		if(!viewName.contains(".do")) {
			view = viewResolver.getView(viewName);
		}else {
			view = viewName;
		}
		
		// 5. 검색된 화면으로 이동한다.
		response.sendRedirect(view);
	}
```
# 최종적 구현
- 각 동작에 맞는 Controller들 구현
- HandlerMapping에서 구현한 Controller 맵핑

# JSP(View) 에서 "<% %>"로 사용되는 Java 코드 제거하기
- EL(Expression Language) : JSP 2.0에서 새로 추가된 스크립트 언어로 ${username} 식으로 접근
- JSTL(JSP Standard Tag Library) : if, for, switch 등 자바 코드를 사용해야 하는 경우 태그 형태로 사용
  - <%@taglib uri="http://java.sun.com/jstl/core_rt" prefix="c" %>
```
<c:forEach items="${boardList }" var="board">
	<tr>
		<td>${board.seq }</td>
		<td>${board.cnt }</td>
	</tr>
</c:forEach>
```