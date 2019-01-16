# �����̽� ���� ����
- <aop:before> : �޼ҵ尡 ����Ǳ� ���� ó���� ������� ����ϱ� ���� ���
- <aop:after-returning> : ������ �޼ҵ尡 ���������� ����ǰ� ����, �޼ҵ� ���� ����� �����ϴ� ������ ����
- <aop:after-throwing> : ������ �޼ҵ尡 ����Ǵٰ� ���ܰ� �߻��ϴ� ������ ����
- <aop:after> : try-catch-finally �������� finally ó�� ���� �߻� ���ο� ������� ������ ����ȴ�.
- <aop:around> : �޼ҵ� ���� ���� �Ŀ� ��� �����Ͽ� ������ ó���Ѵ�.
  - Ŭ���̾�Ʈ�� �޼ҵ� ȣ���� ����æ��.
  - ����æ �� �����̽��� Ŭ���̾�Ʈ�� ȣ���� ����Ͻ� �޼ҵ带 ȣ���ϱ� ���� ProceedingJoinPoint ��ü�� �Ű������� �޾ƾ� �Ѵ�.
  - ProceedingJoinPoint��ü�� proceed() �޼ҵ带 ���ؼ� ����׽� �޼ҵ带 ȣ���� �� �ִ�.
```
import org.aspectj.lang.ProceedingJoinPoint;

public class AroundAdvice {
	public Object aroundLog(ProceedingJoinPoint pjp) throws Throwable{
		System.out.println("[BEFORE] : ����Ͻ� �޼ҵ� ���� ���� ó���� ����...");
		Object returnObj = pjp.proceed();
		System.out.println("[AFTER] : ����׽� �޼ҵ� ���� �Ŀ� ó���� ����...");
		return returnObj;
	}
}
```
