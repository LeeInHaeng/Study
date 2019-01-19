# Spring MVC ����
- ������ ������ �Ͱ� ����ϰ� Controller �������̽��� �����Ѵ�. �� ���⼭ Controller�� ������ �����ӿ�ũ���� �����ϴ� �������̽��̴�.
  - ������ ���� ������ Controller�� String Ÿ���� ��ȯ������, �ش� Controller�� ModelAndView�� ��ȯ�Ѵ�.
```
import org.springframework.web.servlet.mvc.Controller;
import org.springframework.web.servlet.ModelAndView;

public class LoginController implements Controller {
	@Override
	public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response) {
		System.out.println("�α��� ó��");
		...
		// 3. ȭ�� �׺���̼�
		ModelAndView mav = new ModelAndView();
		if(user != null){
			mav.setViewName("getBoardList.do");
		}
		else{
			mav.setViewName("login.jsp");
		}
		// Object�� �����ϱ� ���ؼ���
		mav.addObject("boardList", boardList);

		return mav;
	}
}
```
- DispatcherServlet�� ���� ������ WEB-INF/action-servlet.xml�� HandlerMapping�� Controller�� ����Ѵ�.
```
	<!-- HandlerMapping ��� -->
	<bean class="org.springframework.web.servlet.handler.SimpleUrlHandlerMapping">
		<property name="mappings">
			<props>
				<prop key="/login.do">login</prop>
			</props>
		</property>
	</bean>
	
	<!-- Controller ��� -->
	<bean id="login" class="com.springbook.view.user.LoginController"></bean>
```
- ViewResolver ��� : url�� .jsp(view)�� ���� �Է��ϸ� ������ �߻��ϴµ� �̷��� ������ �ذ��ϱ� ���� ���
  - WEB-INF/board/ �� ������ �ɸ��� .jsp ���ϵ��� �̵� (getBoard.jsp, getBoardList.jsp)
  - action-servlet.xml�� ViewResolver ���
```
	<!-- ViewResolver ��� -->
	<bean id="viewResolver" class="org.springframework.web.servlet.view.InternalResourceViewResolver">
		<property name="prefix" value="/WEB-INF/board/"></property>
		<property name="suffix" value=".jsp"></property>
	</bean>
```
- �� �� ������ ��� ���� jsp�� ȣ���ϸ� ������ �߻��ϴ� Controller�� redirect�� ������ �ʴ´�. �� �ܿ��� redirect�� �ٿ��� ViewResolver�� �����ϵ��� �Ѵ�.
```
// getBoardController�� getBoardListController ---> �̶� ".jsp"�� �����Ѵ�.
		mav.setViewName("getBoard");
		mav.setViewName("getBoardList");
// ������
		if(user != null){
			mav.setViewName("redirect:getBoardList.do");
		}
		else{
			mav.setViewName("redirect:login.jsp");
		}
```