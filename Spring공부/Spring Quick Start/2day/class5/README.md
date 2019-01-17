# AOP ������̼� ���
- ���� ����.xml �� <aop:aspectj-autoproxy></aop:aspectj-autoproxy> ����
- java ���Ͽ��� @Service ������̼� ����
- java ���Ͽ��� Pointcut ������ ���� import org.aspectj.lang.annotation.Pointcut;
- java ���Ͽ��� @Pointcut ������̼� ����
```
@Service
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	@Pointcut("execution(* com.springbook.biz..*Impl.get*(..))")
	public void getPointcut() {}
}
```
- �����̽� ���� : import org.aspectj.lang.annotation.Before;
  - @Before, @AfterReturning, @AfterThrowing, @After, @Around �� ����
```
@Service
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	// <aop:before> ������Ʈ �� pointcut-ref�� �ش���.
	@Before("allPointcut()")
	// <aop:before> ������Ʈ �� method�� �ش���.
	public void printLog() {
		System.out.println("[���� �α�] ����Ͻ� ���� ���� �� ����");
	}
}
```

- �ֽ���Ʈ ���� : import org.aspectj.lang.annotation.Aspect;
  - �ش� ������̼��� ���� ������ �����̳ʴ� �ش� ��ü�� �ֽ���Ʈ ��ü�� �ν��Ѵ�.
```
@Service
@Aspect
public class LogAdvice {
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	// <aop:before> ������Ʈ �� pointcut-ref�� �ش���.
	@Before("allPointcut()")
	// <aop:before> ������Ʈ �� method�� �ش���.
	public void printLog() {
		System.out.println("[���� �α�] ����Ͻ� ���� ���� �� ����");
	}
}
```

# �����̽� ������̼� ����
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

# �� .java �ҽ��ڵ忡 Pointcut ������̼��� �ݺ������� ���� ���� ����
- @Pointcut�� �ݺ������� �ۼ��Ǵ� ���� �����ϱ� ���� class�� ����� �д�.
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
- Ŭ������ ������ ����Ʈ���� �����̽����� ȣ���Ѵ�. (Ŭ���� ��.�޼ҵ�)
```
@Before("PointcutCommon.allPointcut()")
public void printLog() {
	System.out.println("[���� �α�] ����Ͻ� ���� ���� �� ����");
}
```