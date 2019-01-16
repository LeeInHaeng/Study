# 어드바이스 동작 시점
- <aop:before> : 메소드가 실행되기 전에 처리될 내용들을 기술하기 위해 사용
- <aop:after-returning> : 지정된 메소드가 정상적으로 실행되고 나서, 메소드 수행 결과로 리턴하는 시점에 동작
- <aop:after-throwing> : 지정한 메소드가 실행되다가 예외가 발생하는 시점에 동작
- <aop:after> : try-catch-finally 구문에서 finally 처럼 예외 발생 여부에 상관없이 무조건 수행된다.
- <aop:around> : 메소드 실행 전과 후에 모두 동작하여 로직을 처리한다.
  - 클라이언트의 메소드 호출을 가로챈다.
  - 가로챈 후 어드바이스는 클라이언트가 호출한 비즈니스 메소드를 호출하기 위해 ProceedingJoinPoint 객체를 매개변수로 받아야 한다.
  - ProceedingJoinPoint객체의 proceed() 메소드를 통해서 비즈네스 메소드를 호출할 수 있다.
```
import org.aspectj.lang.ProceedingJoinPoint;

public class AroundAdvice {
	public Object aroundLog(ProceedingJoinPoint pjp) throws Throwable{
		System.out.println("[BEFORE] : 비즈니스 메소드 수행 전에 처리할 내용...");
		Object returnObj = pjp.proceed();
		System.out.println("[AFTER] : 비즈네스 메소드 수행 후에 처리할 내용...");
		return returnObj;
	}
}
```
