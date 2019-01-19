# Spring MVC 적용
- 이전에 적용한 것과 비슷하게 Controller 인터페이스를 구현한다. 단 여기서 Controller는 스프링 프레임워크에서 제공하는 인터페이스이다.
  - 이전에 직접 구현한 Controller는 String 타입을 반환했지만, 해당 Controller는 ModelAndView를 반환한다.
```
import org.springframework.web.servlet.mvc.Controller;
import org.springframework.web.servlet.ModelAndView;

public class LoginController implements Controller {
	@Override
	public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response) {
		System.out.println("로그인 처리");
		...
		// 3. 화면 네비게이션
		ModelAndView mav = new ModelAndView();
		if(user != null){
			mav.setViewName("getBoardList.do");
		}
		else{
			mav.setViewName("login.jsp");
		}
		// Object를 저장하기 위해서는
		mav.addObject("boardList", boardList);

		return mav;
	}
}
```
- DispatcherServlet의 설정 파일인 WEB-INF/action-servlet.xml에 HandlerMapping과 Controller를 등록한다.
```
	<!-- HandlerMapping 등록 -->
	<bean class="org.springframework.web.servlet.handler.SimpleUrlHandlerMapping">
		<property name="mappings">
			<props>
				<prop key="/login.do">login</prop>
			</props>
		</property>
	</bean>
	
	<!-- Controller 등록 -->
	<bean id="login" class="com.springbook.view.user.LoginController"></bean>
```
- ViewResolver 사용 : url에 .jsp(view)를 직접 입력하면 문제가 발생하는데 이러한 문제를 해결하기 위해 사용
  - WEB-INF/board/ 에 문제가 될만한 .jsp 파일들을 이동 (getBoard.jsp, getBoardList.jsp)
  - action-servlet.xml에 ViewResolver 등록
```
	<!-- ViewResolver 등록 -->
	<bean id="viewResolver" class="org.springframework.web.servlet.view.InternalResourceViewResolver">
		<property name="prefix" value="/WEB-INF/board/"></property>
		<property name="suffix" value=".jsp"></property>
	</bean>
```
- 이 전 정보가 없어서 직접 jsp를 호출하면 문제가 발생하는 Controller는 redirect를 붙이지 않는다. 그 외에는 redirect를 붙여서 ViewResolver를 무시하도록 한다.
```
// getBoardController와 getBoardListController ---> 이때 ".jsp"를 생략한다.
		mav.setViewName("getBoard");
		mav.setViewName("getBoardList");
// 나머지
		if(user != null){
			mav.setViewName("redirect:getBoardList.do");
		}
		else{
			mav.setViewName("redirect:login.jsp");
		}
```