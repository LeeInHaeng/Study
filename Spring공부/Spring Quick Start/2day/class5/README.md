# AOP 어노테이션 기반
- 설정 파일.xml 에 <aop:aspectj-autoproxy></aop:aspectj-autoproxy> 선언
- java 파일에서 @Service 어노테이션 선언
- java 파일에서 Pointcut 선언을 위해 import org.aspectj.lang.annotation.Pointcut;
- java 파일에서 @Pointcut 어노테이션 설정
```
@Service
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	@Pointcut("execution(* com.springbook.biz..*Impl.get*(..))")
	public void getPointcut() {}
}
```
- 어드바이스 설정 : import org.aspectj.lang.annotation.Before;
  - @Before, @AfterReturning, @AfterThrowing, @After, @Around 가 있음
```
@Service
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	// <aop:before> 엘리먼트 중 pointcut-ref에 해당함.
	@Before("allPointcut()")
	// <aop:before> 엘리먼트 중 method에 해당함.
	public void printLog() {
		System.out.println("[공통 로그] 비즈니스 로직 수행 전 동작");
	}
}
```

- 애스팩트 설정 : import org.aspectj.lang.annotation.Aspect;
  - 해당 어노테이션을 통해 스프링 컨테이너는 해당 객체를 애스팩트 객체로 인식한다.
```
@Service
@Aspect
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	// <aop:before> 엘리먼트 중 pointcut-ref에 해당함.
	@Before("allPointcut()")
	// <aop:before> 엘리먼트 중 method에 해당함.
	public void printLog() {
		System.out.println("[공통 로그] 비즈니스 로직 수행 전 동작");
	}
}
```

# 어드바이스 어노테이션 예제
- Before
```
@Before("allPointcut()")
public void ~
```
- After Returning
```
@AfterReturning(pointcut="getPointcut()", returning="returnObj")
public void afterLog(JoinPoint jp, Object returnObj) ~
```
- After Throwing
```
@AfterThrowing(pointcut="allPointcut()", throwing="exceptObj")
public void exceptionLog(JoinPoint jp, Exception exceptObj) ~
```
- After
```
@After("allPointcut()")
public void ~
```
- Around
```
@Around("allPointcut()")
public Object aroundLog(ProceedingJoinPoint pjp) throws Throwable ~
```

# 각 .java 소스코드에 Pointcut 어노테이션이 반복적으로 들어가는 것을 방지
- @Pointcut이 반복적으로 작성되는 것을 방지하기 위해 class로 만들어 둔다.
```
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;

@Aspect
public class PointcutCommon {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	@Pointcut("execution(* com.springbook.biz..*Impl.get*(..))")
	public void getPointcut() {}
}
```
- 클래스로 만들어둔 포인트컷을 어드바이스에서 호출한다. (클래스 명.메소드)
```
@Before("PointcutCommon.allPointcut()")
public void printLog() {
	System.out.println("[공통 로그] 비즈니스 로직 수행 전 동작");
}
```