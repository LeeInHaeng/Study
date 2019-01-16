# AOP 용어 정리
- Joinpoint : 클라이언트가 호출하는 모든 비즈니스 메소드, '포인트컷 대상' 또는 '포인트컷 후보'라고도 한다.

- Pointcut : 필터링된 조인포인트, 즉 수많은 비즈니스 메소드 중에서 우리가 원하는 특정 메소드에서만 횡단 관심에 해당하는 공통 기능을 수행시키기 위해 필요
  - expression 속성을 이용하여 필터링
```
<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
<aop:pointcut expression="execution(* com.springbook.biz..*Impl.get*(..))" id="getPointcut"/>
```
  - * : 리턴 타입
  - com.springbook.biz.. : 패키지 경로
  - *Impl : 클래스 명
  - *(..) : 메소드명 및 매개 변수

  - 즉 com.springbook.biz 패키지로 시작하는 클래스 중에서 이름이 Impl로 끝나는 클래스에 설정
  - 해당 클레스에서 *(..)은 모든 메소드를 포인트 컷으로 설정하고, get*(..)은 get으로 시작하는 메소드만 포인트컷으로 설정
  - 마지막으로 Advice를 이용하여 pointcut을 참조 및 메소드 설정

- Advice : 횡단 관심에 해당하는 공통 기능의 코드를 의미하며, 독립된 클래스의 메소드로 작성, 언제 동작할지 설정
  - <aop:before>, <aop:after>, <aop:after-returnning>, <aop:throwing>, <aop:round>로 동작 시점 설정
```
<aop:before method="printLog" pointcut-ref="allPointcut"/>
```

- Aspect 또는 Advisor : 어떤 포인트컷 메소드에 대해서 어떤 어드바이스 메소드를 실행할지 결정
```
<bean id="log" class="com.springbook.biz.common.LogAdvice"></bean>
<aop:config>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.get*(..))" id="getPointcut"/>
	<aop:aspect ref="log"> ----> Aspect 또는 Advisor !!중요!!
		<aop:before method="printLog" pointcut-ref="allPointcut"/>
	</aop:aspect>
</aop:config>
```
  - Advisor의 경우에는 포인트컷의 아이디를 모르거나, 메소드 이름을 확인할 수 없을 경우 사용 (트랜잭션 처리)
```
// method 명을 모르기 때문에 advice-ref를 이용하여 advice를 참조
<aop:advisor advice-ref="txAdvice" pointcut-ref="allPointcut"/>
```

# 포인트컷 표현식
- 리턴 타입
  - * : 모든 리턴타입 허용
  - void : 리턴타입이 void인 메소드 선택
  - !void : 리턴타입이 void가 아닌 메소드 선택

- 패키지 경로
  - com.springbook.biz : 정확하게 com.springbook.biz 패키지만 선택
  - com.springbook.biz.. : com.springbook.biz 패키지로 시작하는 모든 패키지 선택
  - com.springbook..impl : com.springbook 패키지로 시작하면서 마지막 패키지 이름이 impl로 끝나는 패키지 선택

- 클래스 명
  - BoardServiceImpl : 정확하게 BoardServiceImpl 클래스만 선택
  - *Impl : 클래스 이름이 Impl로 끝나는 클래스만 선택
  - BoardService+ : BoardService 클래스로부터 파생된 모든 자식 클래스 선택

- 메소드 명
  - *(..) : 가장 기본 설정으로 모든 메소드 선택
  - get*(..) : 메소드 이름이 get으로 시작하는 모든 메소드 선택

- 매개변수 지정
  - (..) : 가장 기본 설정으로서 매개변수의 개수와 타입에 제약이 없음을 의미
  - (*) : 반드시 1개의 매개변수를 가지는 메소드만 선택
  - (com.springbook.user.UserVO) : 매개변수로 UserVO를 가지는 메소드만 선택, 이때 클래스의 패키지 경로가 반드시 포함되어야 한다.
  - (!com.springbook.user.UserVO) : 매개변수로 UserVO를 가지지 않는 메소드만 선택
  - (Integer, ..) : 한 개 이상의 매개변수를 가지되, 첫 번째 매개변수의 타입이 Integer인 메소드만 선택
  - (Integer, *) : 반드시 두 개의 매개변수를 가지되, 첫 번째 매개변수의 타입이 Integer인 메소드만 선택