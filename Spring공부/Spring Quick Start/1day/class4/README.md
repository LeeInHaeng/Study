# 의존성 관리
- Dependency Lookup : 컨테이너가 애플리케이션 운용에 필요한 객체를 생성하고 클라이언트는 컨테이너가 생성한 객체를 검색하여 사용하는 방식
- Dependency Injection : 객체 사이의 의존관계를 스프링 설정 파일에 등록된 정보를 바탕으로 컨테이너가 자동으로 처리 ---> 대부분의 경우 이 방식을 사용

# Dependency Injection 중 생성자 인젝션 이용
- 매개변수가 있는 생성자를 선언 (SamsungTV.java)
- XML 설정 파일에서 constructor-arg 엘리먼트를 추가하여 생성자 매개변수로 넘겨줌
  - ref 속성으로 bean 참조
  - 만약 2개 이상의 매개변수가 필요하면 constructor-arg를 매개변수 갯수만큼 설정 (값 설정의 경우는 value)

# Dependency Injection 중 Setter 인젝션 이용
- set메소드 생성 (SamsungTV.java) ex) public void setSpeaker(Speaker speaker)
- XML 설정 파일에서 property 엘리먼트를 추가하여 ref, value 속성 등을 설정
  - name 속성의 경우 .java에서 set을 없앤 소문자로 시작 (ex1 : setSpeaker() ---> name="speaker" , ex2 : setBoardDAO() ---> name="boardDAO")

# Setter 인젝션 설정 시 p 네임스페이스 사용하는 방법
- XML 설정 파일에서 xmlns:p="http://www.springframework.org/schema/p" 설정
- p:변수명-ref="참조할 객체의 이름이나 아이디"
- p:변수명="설정할 값"

# List 타입 매핑
- java에서 import java.util.List;
- java에서 List 사용 (ex : private List<String> addressList;)
- XML 설정 파일에서 list 엘리먼트 사용, 값 설정은 value 엘리먼트로 설정
```
<list>
	<value>서울시 강남구 역삼동</value>
	<value>서울시 성동구 행당동</value>
</list>
```

# Set 타입 매핑
- java에서 import java.util.Set;
- java에서 Set 사용 (ex : private Set<String> addressList;)
- XML 설정 파일에서 set 엘리먼트 사용, 값 설정은 value 엘리먼트로 설정
```
<set value-type="java.lang.String">
	<value>서울시 강남구 역삼동</value>
	<value>서울시 성동구 성수동</value>
	<value>서울시 성동구 성수동</value>
</set>
```

# Map 타입 매핑
- java에서 import java.util.Map;
- java에서 Set 사용 (ex : private Map<String, String> addressList;)
- XML 설정 파일에서 map 엘리먼트 사용, 각 키 당 entry 엘리먼트 사용, 키 값은 key 엘리먼트 사용, 값 설정은 value 엘리먼트로 설정
```
<map>
	<entry>
		<key><value>고길동</value></key>
		<value>서울시 강남구 역삼동</value>
	</entry>
	<entry>
		<key><value>마이콜</value></key>
		<value>서울시 강서구 화곡동</value>
	</entry>
</map>
```

# Properties 타입 매핑
- java에서 import java.util.Properties;
- java에서 Properties 사용 (ex : private Properties addressList;)
- XML 설정 파일에서 props 엘리먼트 사용, prop 엘리먼트로 키와 벨류 값 설정
```
<props>
	<prop key="고길동">서울시 강남구 역삼동</prop>
	<prop key="마이콜">서울시 강남구 화곡동</prop>
</props>
```