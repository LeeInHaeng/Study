# 트랜잭션 처리 사용
- 데이터베이스와 연동된 메소드를 수행할 때 제대로 동작되는지 여부를 확인하기 위해 사용
  - ex) insertBoard 등
- 어떠한 메소드가 수행 중에 문제가 발생하면 Advice를 참조하여 rollback() 메소드를 호출한다.
- 만약 문제없이 정상으로 수행되었다면 commit() 메소드를 호출한다.

# 트랜잭션 처리 적용
- Namespaces 탭에서 tx를 추가
- 트랜잭션 관리자를 설정파일.xml에 bean으로 등록
  - JDBC 기반 동작은 DataSourceTransactionManager 클래스를 이용
  - JPA를 이용한 경우는 JPATransactionManager 를 등록
```
	 <!-- DataSource 설정 -->
	 <context:property-placeholder location="classpath:config/database.properties"/>
	 
	 <bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	 	<property name="driverClassName" value="${jdbc.driver}"/>
	 	<property name="url" value="${jdbc.url}"/>
	 	<property name="username" value="${jdbc.username}"/>
	 	<property name="password" value="${jdbc.password}"/>
	 </bean>
	 
	 <!-- Transaction 설정 -->
	 <bean id="txManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
	 	<property name="dataSource" ref="dataSource"></property>
	 </bean>
```
- tx:advice 엘리먼트를 사용하여 트랜잭션 어드바이스 설정
  - get으로 시작하는 모든 메소드는 읽기 전용으로 처리되어 트랜잭션 관리 대상으로 제외
  - 나머지 메소드들은 트랜잭션 관리에 포함
  - name, read-only, no-rollback-for, rollback-for 속성이 있다.
```
	 <!-- DataSource 설정 -->
	 <context:property-placeholder location="classpath:config/database.properties"/>
	 
	 <bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	 	<property name="driverClassName" value="${jdbc.driver}"/>
	 	<property name="url" value="${jdbc.url}"/>
	 	<property name="username" value="${jdbc.username}"/>
	 	<property name="password" value="${jdbc.password}"/>
	 </bean>
	 
	 <!-- Transaction 설정 -->
	 <bean id="txManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
	 	<property name="dataSource" ref="dataSource"></property>
	 </bean>
	 
	 <tx:advice id="txAdvice" transaction-manager="txManager">
	 	<tx:attributes>
	 		<tx:method name="get*" read-only="true"/>
	 		<tx:method name="*"/>
	 	</tx:attributes>
	 </tx:advice>
```
- aop 설정을 통해 트랜잭션 적용
  - aspect가 아닌 <aop:advisor> 엘리먼트를 사용하여 어드바이스와 포인트컷을 바인딩한다.
```
	 <tx:advice id="txAdvice" transaction-manager="txManager">
	 	<tx:attributes>
	 		<tx:method name="get*" read-only="true"/>
	 		<tx:method name="*"/>
	 	</tx:attributes>
	 </tx:advice>
	 
	 <aop:config>
	 	<aop:pointcut id="txPointcut" expression="execution(* com.springbook.biz..*(..))"/>
	 	<aop:advisor pointcut-ref="txPointcut" advice-ref="txAdvice"/>
	 </aop:config>
```
