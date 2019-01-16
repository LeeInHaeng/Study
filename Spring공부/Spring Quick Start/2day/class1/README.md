# ���� �������� ���� ���յ�
- IoC(Inversion of Control) : ���յ��� ���õ� ��� (���� ���յ��� ����)
- AOP(Aspect Oriented Programming) : �������� ���õ� ��� (���� �������� ����)
  - Ⱦ�� ����(Crosscutting Concerns) : �޼ҵ帶�� �������� �����ϴ� �α��̳� ����, Ʈ����� ó�� ���� �ڵ��
  - �ٽ� ����(Core Concerns) : ������� ��û�� ���� ������ ����Ǵ� �ٽ� ����Ͻ� ����
  - OOP������ Ⱦ�� ���ɰ� �ٽ� ������ �и��� �� ������, AOP�� �̷��� �Ѱ踦 �غ��� �� �ֵ��� �����ش�.

# AOP ���̺귯�� ���
- pom.xml���� AOP ���̺귯�� �߰�
```
<!-- AspectJ -->
<dependency>
	<groupId>org.aspectj</groupId>
	<artifactId>aspectjrt</artifactId>
	<version>${org.aspectj-version}</version>
</dependency>
<dependency>
	<groupId>org.aspectj</groupId>
	<artifactId>aspectjweaver</artifactId>
	<version>1.8.8</version>
</dependency>
```
- ��������.xml�� Namespaces �ǿ��� aop�� �߰�
- <bean> ��� �� <aop:config>�� �̿��Ͽ� ����
```
<bean id="log" class="com.springbook.biz.common.LogAdvice"></bean>
<aop:config>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
	 <aop:aspect ref="log">
	 	<aop:before method="printLog" pointcut-ref="allPointcut"/>
	 </aop:aspect>
</aop:config>
```