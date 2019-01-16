# 높은 응집도와 낮은 결합도
- IoC(Inversion of Control) : 결합도와 관련된 기능 (낮은 결합도를 위해)
- AOP(Aspect Oriented Programming) : 응집도와 관련된 기능 (높은 응집도를 위해)
  - 횡단 관심(Crosscutting Concerns) : 메소드마다 공통으로 등장하는 로깅이나 예외, 트랜잭션 처리 같은 코드들
  - 핵심 관심(Core Concerns) : 사용자의 요청에 따라 실제로 수행되는 핵심 비즈니스 로직
  - OOP에서는 횡단 관심과 핵심 관심을 분리할 수 없지만, AOP는 이러한 한계를 극복할 수 있도록 도와준다.

# AOP 라이브러리 사용
- pom.xml에서 AOP 라이브러리 추가
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
- 설정파일.xml의 Namespaces 탭에서 aop를 추가
- <bean> 등록 후 <aop:config>를 이용하여 설정
```
<bean id="log" class="com.springbook.biz.common.LogAdvice"></bean>
<aop:config>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
	 <aop:aspect ref="log">
	 	<aop:before method="printLog" pointcut-ref="allPointcut"/>
	 </aop:aspect>
</aop:config>
```