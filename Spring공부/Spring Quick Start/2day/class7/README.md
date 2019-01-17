# Ʈ����� ó�� ���
- �����ͺ��̽��� ������ �޼ҵ带 ������ �� ����� ���۵Ǵ��� ���θ� Ȯ���ϱ� ���� ���
  - ex) insertBoard ��
- ��� �޼ҵ尡 ���� �߿� ������ �߻��ϸ� Advice�� �����Ͽ� rollback() �޼ҵ带 ȣ���Ѵ�.
- ���� �������� �������� ����Ǿ��ٸ� commit() �޼ҵ带 ȣ���Ѵ�.

# Ʈ����� ó�� ����
- Namespaces �ǿ��� tx�� �߰�
- Ʈ����� �����ڸ� ��������.xml�� bean���� ���
  - JDBC ��� ������ DataSourceTransactionManager Ŭ������ �̿�
  - JPA�� �̿��� ���� JPATransactionManager �� ���
```
	 <!-- DataSource ���� -->
	 <context:property-placeholder location="classpath:config/database.properties"/>
	 
	 <bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	 	<property name="driverClassName" value="${jdbc.driver}"/>
	 	<property name="url" value="${jdbc.url}"/>
	 	<property name="username" value="${jdbc.username}"/>
	 	<property name="password" value="${jdbc.password}"/>
	 </bean>
	 
	 <!-- Transaction ���� -->
	 <bean id="txManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
	 	<property name="dataSource" ref="dataSource"></property>
	 </bean>
```
- tx:advice ������Ʈ�� ����Ͽ� Ʈ����� �����̽� ����
  - get���� �����ϴ� ��� �޼ҵ�� �б� �������� ó���Ǿ� Ʈ����� ���� ������� ����
  - ������ �޼ҵ���� Ʈ����� ������ ����
  - name, read-only, no-rollback-for, rollback-for �Ӽ��� �ִ�.
```
	 <!-- DataSource ���� -->
	 <context:property-placeholder location="classpath:config/database.properties"/>
	 
	 <bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	 	<property name="driverClassName" value="${jdbc.driver}"/>
	 	<property name="url" value="${jdbc.url}"/>
	 	<property name="username" value="${jdbc.username}"/>
	 	<property name="password" value="${jdbc.password}"/>
	 </bean>
	 
	 <!-- Transaction ���� -->
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
- aop ������ ���� Ʈ����� ����
  - aspect�� �ƴ� <aop:advisor> ������Ʈ�� ����Ͽ� �����̽��� ����Ʈ���� ���ε��Ѵ�.
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
