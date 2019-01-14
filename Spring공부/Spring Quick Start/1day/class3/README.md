# 스프링 컨테이너 및 설정 파일
- 프로젝트의 src/main/resources에 Spring Bean Configuration File을 생성
  - 만든 xml 파일에 bean 엘리먼트 입력 (id와 class)

# 스프링 컨테이너 구동 및 테스트
- 1. Spring 컨테이너를 구동한다.
  - import org.springframework.context.support.AbstractApplicationContext;
  - import org.springframework.context.support.GenericXmlApplicationContext;
  - AbstractApplicationContext factory = new GenericXmlApplicationContext("위에서 만든.xml");

- 2. Spring 컨테이너로부터 필요한 객체를 요청(Lookup) 한다.
  - TV tv = (TV)factory.getBean("tv");
  - getBean 안의 인자는 xml파일 내에 생성한 bean 엘리먼트의 id를 넣는다.
  - 해당 id에 매칭되는 class를 얻을 수 있다.

- 3. Spring 컨테이너를 종료한다.
  - factory.close();

# ApplicationContext
- BeanFactory가 제공하는 bean 객체 관리 기능 + 트랜잭션 관리 + 메시지 기반의 다국어 처리 등 다양한 기능
- 컨테이너가 구동되는 시점에 bean 등록된 클래스들을 객체 생성하는 즉시 로딩 방식으로 동작
- 웹 애플리케이션 개발 또한 지원
- GenericXmlApplicationContext : 파일 시스템이나 클래스 경로에 있는 XML 설정 파일을 로딩하여 구동하는 컨테이너
- XmlWebApplicationContext : 웹 기반의 스프링 애플리케이션을 개발할 때 사용하는 컨테이너

# 스프링 XML 설정
- import 엘리먼트 : 여러 설정이 되어 있는 다른 xml 파일을 import 한다.
  - <import resource="myxml.xml"/>

- bean 엘리먼트 : 스프링 설정 파일에 클래스를 등록하기 위해 사용
  - id는 생략이 가능하지만 class는 필수 속성 <bean id="~" class="~"></bean>
  - name 속성 또한 id와 마찬가지로 전체 스프링 파일 내에서 유일해야 하지만 특수기호 포함이 가능하다.

# bean 엘리먼트 속성
- init-method 속성 : 객체 생성 후 생성자 호출 후에 멤버변수 초기화 작업이 필요한 경우 주로 사용
  - <bean id="tv" class="SamsungTV" init-method="initMethod"/>
  - SamsungTV.java에서 public void initMethod() 생성

- destroy-method 속성 : 스프링 컨테이너가 객체를 삭제하기 직전에 호출되는 임의의 메소드를 지정할 수 있다.
  - <bean id="tv" class="SamsungTV" destroy-method="destroyMethod"/>
  - SamsungTV.java에서 public void destroyMethod() 생성

- lazy-init 속성 : 자주 사용되지 않는 bean의 경우 메모리를 많이 차지하여 부담을 줄 수 있기 때문에 bean이 사용되는 시점에 객체를 생성하도록 하는 속성
  - <bean ~~ lazy-init="true"/>

- scope 속성 : 각 객체만의 특성이 없는 경우 하나의 객체만 생성돼도 되기 때문에 필요한 속성
  - <bean ~~ scope="singleton"/> ---> 대부분 싱글톤으로 운영 되는 것이 바람직하다.
  - 매번 새로운 객체를 생성하고 싶다면 scope="prototype"으로 지정