# Spring MVC ���� �帧
![123](https://user-images.githubusercontent.com/20277647/51423186-51882c80-1bff-11e9-8c61-9b586f0f01ad.png)
- 1. Ŭ���̾�Ʈ�κ����� ��� ",do" ��û�� DispatcherServlet�� �޴´�.
- 2. DispatcherServlet�� HandlerMapping�� ���� ��û�� ó���� Controller�� �˻��Ѵ�.
- 3. DispatcherServlet�� �˻��� Controller�� �����Ͽ� Ŭ���̾�Ʈ�� ��û�� ó���Ѵ�.
- 4. Controller�� ����Ͻ� ������ ���� ����� �� Model ������ Model�� ������ View ������ ModelAndView ��ü�� �����Ͽ� �����Ѵ�.
- 5. DispatcherServlet�� ModelAndView�κ��� View ������ �����ϰ�, ViewResolver�� �̿��Ͽ� �������� ����� View�� ����.
- 6. DispatcherServlet�� ViewResolver�� ���� ã�Ƴ� View�� �����Ͽ� ������ �����Ѵ�.

# Spring MVC ����
- src/main/webapp/WEB-INF/web.xml�� ������ �����ӿ�ũ���� �����ϴ� DispatcherServlet ���
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
- �ش� DispatcherServlet�� '�����̸�-servlet.xml' ���������� ã�´�. ��, action-servlet.xml �̶�� ���� ������ ã�´�. �׷��� ������ WEB-INF�� Spring Bean Configuration File�� action-servlet.xml�� �����.
  - web.xml���� init-param�� �̿��Ͽ� ��� �� ���ϸ��� ����ڰ� ���ϴ� ������� �� ���� �ִ�.
- web.xml�� ���ڵ� ó���� ���� CharacterEncodingFilter Ŭ������ ���ͷ� ����Ѵ�. (�ѱ� ���� ����)
  - url-pattern ������Ʈ�� "*.do"�� ���� ".do" ��û�� ���� �ϰ������� ���ڵ� ó���� �Ѵ�.
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
