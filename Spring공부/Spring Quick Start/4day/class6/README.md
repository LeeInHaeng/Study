# �ٱ��� ó��
- webapp/WEB-INF/messages�� �� �� �´� �޽��� ���� �ۼ� (message_���.properties)
- ������ ��������(action-servlet.xml)�� �ۼ��� �޽��� ������ bean�� ���
```
	<!-- �ٱ��� ���� -->
	<!-- MessageSource ��� -->
	<bean id="messageSource" class="org.springframework.context.support.ReloadableResourceBundleMessageSource">
		<property name="basenames">
			<list>
				<value>/WEB-INF/messages/message</value>
			</list>
		</property>
		<property name="defaultEncoding" value="UTF-8" />
		<property name="cacheSeconds" value="30" />
	</bean>
```
- LocaleResolver ���
```
	<!-- LocaleResolver ��� -->
	<bean id="localeResolver" class="org.springframework.web.servlet.i18n.SessionLocaleResolver"></bean>
```
- mvc ���ӽ����̽� �߰� �� LocaleChangeInterceptor ���
```
	<!-- LocaleChangeInterceptor ��� -->
	<mvc:interceptors>
		<bean class="org.springframework.web.servlet.i18n.LocaleChangeInterceptor">
			<property name="paramName" value="lang"/>
		</bean>
	</mvc:interceptors>
```
- �ٱ��� ó���� ���� jsp���� taglib ���� �� ���
```
<%@taglib uri="http://www.springframework.org/tags" prefix="spring" %>

<title><spring:message code="message.user.login.title"/></title>

- ���� ���ذ�
  - No message found under code 'message.user.login.title' for locale 'ko_KR'.
  - �ƹ������� ��� �߸����ִ��� �𸣰���