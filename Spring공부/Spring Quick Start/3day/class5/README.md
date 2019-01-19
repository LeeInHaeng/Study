# Spring MVC 수행 흐름
![123](https://user-images.githubusercontent.com/20277647/51423186-51882c80-1bff-11e9-8c61-9b586f0f01ad.png)
- 1. 클라이언트로부터의 모든 ",do" 요청을 DispatcherServlet이 받는다.
- 2. DispatcherServlet은 HandlerMapping을 통해 요청을 처리할 Controller를 검색한다.
- 3. DispatcherServlet은 검색된 Controller를 실행하여 클라이언트의 요청을 처리한다.
- 4. Controller는 비즈니스 로직의 수행 결과로 얻어낸 Model 정보와 Model을 보여줄 View 정보를 ModelAndView 객체에 저장하여 리턴한다.
- 5. DispatcherServlet은 ModelAndView로부터 View 정보를 추출하고, ViewResolver를 이용하여 응답으로 사용할 View를 얻어낸다.
- 6. DispatcherServlet은 ViewResolver를 통해 찾아낸 View를 실행하여 응답을 전송한다.

# Spring MVC 적용
- src/main/webapp/WEB-INF/web.xml에 스프링 프레임워크에서 제공하는 DispatcherServlet 사용
```
  <servlet>
    <servlet-name>action</servlet-name>
    <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
  </servlet>
  <servlet-mapping>
    <servlet-name>action</servlet-name>
    <url-pattern>*.do</url-pattern>
  </servlet-mapping>
```
- 해당 DispatcherServlet은 '서블릿이름-servlet.xml' 설정파일을 찾는다. 즉, action-servlet.xml 이라는 설정 파일을 찾는다. 그렇기 때문에 WEB-INF에 Spring Bean Configuration File로 action-servlet.xml을 만든다.
  - web.xml에서 init-param을 이용하여 경로 및 파일명을 사용자가 원하는 방식으로 줄 수도 있다.
- web.xml에 인코딩 처리를 위해 CharacterEncodingFilter 클래스를 필터로 등록한다. (한글 깨짐 방지)
  - url-pattern 엘리먼트에 "*.do"를 통해 ".do" 요청에 대해 일괄적으로 인코딩 처리를 한다.
```
  <filter>
  	<filter-name>characterEncoding</filter-name>
  	<filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
  	<init-param>
  		<param-name>encoding</param-name>
  		<param-value>EUC-KR</param-value>
  	</init-param>
  </filter>
  
  <filter-mapping>
  	<filter-name>characterEncoding</filter-name>
  	<url-pattern>*.do</url-pattern>
  </filter-mapping>
```
