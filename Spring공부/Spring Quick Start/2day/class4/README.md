# JoinPoint �޼ҵ�
- Signature getSignature() : Ŭ���̾�Ʈ�� ȣ���� �޼ҵ��� �ñ״�ó(����Ÿ��, �̸�, �Ű�����) ������ ����� Signature ��ü ����
- Object getTarget() : Ŭ���̾�Ʈ�� ȣ���� ����Ͻ� �޼ҵ带 �����ϴ� ����Ͻ� ��ü ����
- Object[] getArgs() : Ŭ���̾�Ʈ�� �޼ҵ带 ȣ���� �� �Ѱ��� ���� ����� Object �迭�� ����
- Around�� ProceedingJoinPoint�� ��������� Before, After ���� JoinPoint�� ����Ѵ�. (proceed �޼ҵ� ���� ����)
- Signature�� �����ϴ� �޼ҵ�
  - String getName() : Ŭ���̾�Ʈ�� ȣ���� �޼ҵ� �̸� ����
  - String toLongString() : Ŭ���̾�Ʈ�� ȣ���� �޼ҵ��� ����Ÿ��, �̸�, �Ű������� ��Ű�� ��α��� �����Ͽ� ����
  - String toShortString() : Ŭ���̾�Ʈ�� ȣ���� �޼ҵ� �ñ״�ó�� ����� ���ڿ��� ����
- before ����
```
import org.aspectj.lang.JoinPoint;

public class BeforeAdvice {
	public void beforeLog(JoinPoint jp) {
		String method = jp.getSignature().getName();
		Object[] args = jp.getArgs();
		
		System.out.println("[���� ó��] " + method + "() �޼ҵ� ARGS ���� : " + args[0].toString());
	}
}
```
- after returning ����
```
import org.aspectj.lang.JoinPoint;
import com.springbook.biz.user.UserVO;

public class AfterReturningAdvice {
	public void afterLog(JoinPoint jp, Object returnObj) {
		String method = jp.getSignature().getName();
		if(returnObj instanceof UserVO) {
			UserVO user = (UserVO) returnObj;
			if(user.getRole().equals("Admin")) {
				System.out.println(user.getName() + " �α���(Admin)");
			}
		}
		
		System.out.println("[���� ó��] " + method + "() �޼ҵ� ���ϰ� : " + returnObj.toString());
	}
}

// xml����
<aop:after-returning method="afterLog" pointcut-ref="getPointcut" returning="returnObj"/>
```
  - returning �Ӽ��� after-returning ������ ����� �� �ִ� �Ӽ�
  - �� �Ӽ����� �ݵ�� �����̽� �޼ҵ� �Ű������� ����� ���ε� ���� �̸��� ���ƾ� �Ѵ�.
- after throwing ����
```
public void exceptionLog(JoinPoint jp, Exception exceptObj)

// xml����
<aop:after-throwing ~~ throwing="exceptObj"/>
```
  - throwing �Ӽ��� after-throwing ������ ����� �� �ִ� �Ӽ�
  - �� �Ӽ����� �ݵ�� �����̽� �޼ҵ� �Ű������� ����� ���ε� ���� �̸��� ���ƾ� �Ѵ�.