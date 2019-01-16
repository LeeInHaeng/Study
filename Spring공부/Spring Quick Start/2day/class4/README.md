# JoinPoint 메소드
- Signature getSignature() : 클라이언트가 호출한 메소드의 시그니처(리턴타입, 이름, 매개변수) 정보가 저장된 Signature 객체 리턴
- Object getTarget() : 클라이언트가 호출한 비즈니스 메소드를 포함하는 비즈니스 객체 리턴
- Object[] getArgs() : 클라이언트가 메소드를 호출할 때 넘겨준 인자 목록을 Object 배열로 리턴
- Around는 ProceedingJoinPoint를 사용하지만 Before, After 등은 JoinPoint를 사용한다. (proceed 메소드 유무 차이)
- Signature가 제공하는 메소드
  - String getName() : 클라이언트가 호출한 메소드 이름 리턴
  - String toLongString() : 클라이언트가 호출한 메소드의 리턴타입, 이름, 매개변수를 패키지 경로까지 포함하여 리턴
  - String toShortString() : 클라이언트가 호출한 메소드 시그니처를 축약한 문자열로 리턴
- before 예제
```
import org.aspectj.lang.JoinPoint;

public class BeforeAdvice {
	public void beforeLog(JoinPoint jp) {
		String method = jp.getSignature().getName();
		Object[] args = jp.getArgs();
		
		System.out.println("[사전 처리] " + method + "() 메소드 ARGS 정보 : " + args[0].toString());
	}
}
```
- after returning 예제
```
import org.aspectj.lang.JoinPoint;
import com.springbook.biz.user.UserVO;

public class AfterReturningAdvice {
	public void afterLog(JoinPoint jp, Object returnObj) {
		String method = jp.getSignature().getName();
		if(returnObj instanceof UserVO) {
			UserVO user = (UserVO) returnObj;
			if(user.getRole().equals("Admin")) {
				System.out.println(user.getName() + " 로그인(Admin)");
			}
		}
		
		System.out.println("[사후 처리] " + method + "() 메소드 리턴값 : " + returnObj.toString());
	}
}

// xml에서
<aop:after-returning method="afterLog" pointcut-ref="getPointcut" returning="returnObj"/>
```
  - returning 속성은 after-returning 에서만 사용할 수 있는 속성
  - 이 속성값은 반드시 어드바이스 메소드 매개변수로 선언된 바인드 변수 이름과 같아야 한다.
- after throwing 예제
```
public void exceptionLog(JoinPoint jp, Exception exceptObj)

// xml에서
<aop:after-throwing ~~ throwing="exceptObj"/>
```
  - throwing 속성은 after-throwing 에서만 사용할 수 있는 속성
  - 이 속성값은 반드시 어드바이스 메소드 매개변수로 선언된 바인드 변수 이름과 같아야 한다.