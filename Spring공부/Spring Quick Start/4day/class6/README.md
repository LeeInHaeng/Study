# 다국어 처리
- webapp/WEB-INF/messages에 각 언어에 맞는 메시지 파일 작성 (message_언어.properties)
- 스프링 설정파일(action-servlet.xml)에 작성한 메시지 파일을 bean에 등록
```
	<!-- 다국어 설정 -->
	<!-- MessageSource 등록 -->
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
- LocaleResolver 등록
```
	<!-- LocaleResolver 등록 -->
	<bean id="localeResolver" class="org.springframework.web.servlet.i18n.SessionLocaleResolver"></bean>
```
- mvc 네임스페이스 추가 후 LocaleChangeInterceptor 등록
```
	<!-- LocaleChangeInterceptor 등록 -->
	<mvc:interceptors>
		<bean class="org.springframework.web.servlet.i18n.LocaleChangeInterceptor">
			<property name="paramName" value="lang"/>
		</bean>
	</mvc:interceptors>
```
- 다국어 처리를 위한 jsp에서 taglib 선언 후 사용
```
<%@taglib uri="http://www.springframework.org/tags" prefix="spring" %>

<title><spring:message code="message.user.login.title"/></title>

- 에러 미해결
  - No message found under code 'message.user.login.title' for locale 'ko_KR'.
  - 아무리봐도 어디가 잘못되있는지 모르겠음