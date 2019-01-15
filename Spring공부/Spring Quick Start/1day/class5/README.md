# Context 네임스페이스
- STS Namespaces 탭에서 context 선택 후 추가

- 스프링 설정 파일에 사용할 객체들을 <bean> 에 등록하지 않고 자동으로 생성하기 위해 <context:component-scan> 사용
  - XML 설정 파일에서 <context:component-scan base-package="패키지명"></context:component-scan>

- .java 파일에 Annotation 설정 : @ComponentScan("tv")
  - import org.springframework.stereotype.Component;

# 어노테이션
- @Autowired : 주로 변수 위에 설정하여 해당 타입의 객체를 찾아서 자동으로 할당
  - import org.springframework.beans.factory.annotation.Autowired;
```
@Autowired
private Speaker speaker;
```
  - 의존성 주입에 사용했던 Setter 메소드나 생성자가 필요 없이 자동으로 객체 생성
  - 단, 해당 객체가 메모리에 올라가 있어야 하므로 SonySpeaker.java 에도 @Component("sony") 설정

- @Qualifier : 특정 객체의 이름을 이용하여 의존성 주입할 때 사용
  - Autowired에서 메모리에 올라온 객체가 2개 이상일 때 충돌이 발생하므로 해당 어노테이션을 사용
  - import org.springframework.beans.factory.annotation.Qualifier;
```
@Autowired
@Qualifier("apple")
private Speaker speaker;
```

- @Resource : @Autowired와 @Qualifier을 합친 어노테이션, Spring 어노테이션이 아닌 자바 기존의 어노테이션
  - import javax.annotation.Resource;
```
@Resource(name="apple")
private Speaker speaker;
```

- 위의 Speaker 객체처럼 변경될 수 있는 부분은 xml에서 <bean>으로 등록 후, Autowired 어노테이션만 사용하는 방법도 있음. (Component 어노테이션을 지워서 객체가 자동으로 메모리에 올라가는 것을 없앤다.)
  - XML만 설정하기에는 <bean> 등록이 많아지고 의존 관계 설정이 부담스럽다.
  - 어노테이션만 사용하자니 자바 소스를 수정해야 의존 관계를 변경할 수 있다.
  - 즉 두 가지 방식을 병행해서 적절히 사용!
```
@Autowired
private Speaker speaker;

<bean class="polymorphism.SonySpeaker"></bean>
```