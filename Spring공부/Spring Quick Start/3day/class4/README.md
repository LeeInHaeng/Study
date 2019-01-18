# MVC �����ӿ�ũ ����
- �ϳ��� ���� Ŭ������ ��� ��û�� ó���ϱ⿡�� �ڵ尡 ����������.
- ���������� Spring MVC�� �̿��� ��������, Spring MVC�� �����ϱ� ������ ����� ������ �ϵ��� ���� �����غ���.
- ������ Ŭ����
  - DispatcherServlet : ������ ���� Ŭ�����μ� ��� Ŭ���̾�Ʈ�� ��û�� ���� ���� ó���ϴ� Front Controller
  - HandlerMapping : Ŭ���̾�Ʈ�� ��û�� ó���� Controller ����
  - Controller : �������� Ŭ���̾�Ʈ�� ��û ó��
  - ViewResolver : Controller�� ������ View �̸����� ����� JSP ��� �ϼ�
- Ŭ���̾�Ʈ�� ��û�� ���� DispatcherServlet�� HandlerMapping�� ���� Controller ��ü�� �˻��ϰ�, �˻��� Controller�� ����

# Controller ����
- � Controller ��ü�� �˻��Ǵ��� ���� �ڵ�� �����ϱ� ���� Controller�� �ֻ��� �������̽��� ����
```
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public interface Controller {
	String handleRequest(HttpServletRequest request, HttpServletResponse response);
}
```
- �ֻ��� �������̽��� �̿��� ��Ʈ�ѷ� ����
```
public class LoginController implements Controller {
	@Override
	public String handleRequest(HttpServletRequest request, HttpServletResponse response) {
		System.out.println("�α��� ó��");
		...
		return "getBoardList.do";
		Ȥ��
		return "login"; // login.jsp�� �ƴ� login
	}
}
```

# HandlerMapping Ŭ���� ����
- ��� Controller ��ü���� �����ϰ� �ִٰ�, Ŭ���̾�Ʈ�� ��û�� ������ ��û�� ó���� Ư�� Controller�� �˻��ϴ� ����� ����
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

# ViewResolver Ŭ���� ����
- Controller�� ������ View �̸��� ���λ�, ���̻縦 �����Ͽ� �������� ����� View ��ο� ���ϸ��� �ϼ�
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
# DispatcherServlet ����
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
		// 1. Ŭ���̾�Ʈ�� ��û path ������ ����
		String uri = request.getRequestURI();
		String path = uri.substring(uri.lastIndexOf("/"));
		
		// 2. HandlerMapping�� ���� path�� �ش��ϴ� Controller�� �˻��Ѵ�.
		Controller ctrl = handlerMapping.getController(path);
		
		// 3. �˻��� Controller�� �����Ѵ�.
		String viewName = ctrl.handleRequest(request, response);
		
		// 4. ViewResolver�� ���� viewName�� �ش��ϴ� ȭ���� �˻��Ѵ�.
		String view = null;
		if(!viewName.contains(".do")) {
			view = viewResolver.getView(viewName);
		}else {
			view = viewName;
		}
		
		// 5. �˻��� ȭ������ �̵��Ѵ�.
		response.sendRedirect(view);
	}
```
# ������ ����
- �� ���ۿ� �´� Controller�� ����
- HandlerMapping���� ������ Controller ����

# JSP(View) ���� "<% %>"�� ���Ǵ� Java �ڵ� �����ϱ�
- EL(Expression Language) : JSP 2.0���� ���� �߰��� ��ũ��Ʈ ���� ${username} ������ ����
- JSTL(JSP Standard Tag Library) : if, for, switch �� �ڹ� �ڵ带 ����ؾ� �ϴ� ��� �±� ���·� ���
  - <%@taglib uri="http://java.sun.com/jstl/core_rt" prefix="c" %>
```
<c:forEach items="${boardList }" var="board">
	<tr>
		<td>${board.seq }</td>
		<td>${board.cnt }</td>
	</tr>
</c:forEach>
```