# JPA (Java Persistence API) 의 개념
- ORM(Object-Relation Mapping)은 DB 연동에 필요한 SQL을 자동으로 생성하고, 생성된 SQL은 DBMS가 변경될 때 자동으로 변경된다.
- ORM 프레임워크로 Hibernate, TopLink, Cocobase 등이 등장했다.
- 이러한 많은 프레임워크들에 대해 표준화 작업이 필요했고, ORM 구현체들의 공통 인터페이스를 제공하는 것이 JPA다.
![123](https://user-images.githubusercontent.com/20277647/51786929-84599400-21ae-11e9-80c5-c4abb5edf379.png)

# 프로젝트에서 JPA 사용
- 프로젝트 우클릭 ---> Properties ---> Project Facets ---> Convert to faceted form ---> JPA 체크
- JPA에서 Runtimes 탭의 jdk 체크, Further configuration available 클릭 ---> JPA Implementation 항목에서 Type을 Disable Library Configuration으로 선택
- JPA 라이브러리를 추가하기 위해 pom.xml에서 dependency 추가, 사용할 데이터베이스 dependency 추가
```
  	<!-- JPA, 하이버네이트 -->
  	<dependency>
  		<groupId>org.hibernate</groupId>
  		<artifactId>hibernate-entitymanager</artifactId>
  		<version>5.1.0.Final</version>
  	</dependency>

  	<!-- H2 데이터베이스 -->
  	<dependency>
  		<groupId>com.h2database</groupId>
  		<artifactId>h2</artifactId>
  		<version>1.4.197</version>
  	</dependency>
```
- 엔티티 클래스 생성 (VO 클래스와 비슷)
  - 패키지에서 우클릭 ---> New ---> JPA Entity ---> Class name 입력 후 Finish
  - Entity 어노테이션 : 엔티티 클래스를 의미하며 테이블과 매핑된다.
  - Table 어노테이션 : 엔티티와 관련된 테이블을 매핑, name 속성을 생략 시 클래스 이름이 테이블 이름과 매핑된다.
  - Id 어노테이션 : 필수 어노테이션으로, 특정 변수를 테이블의 기본 키와 매핑
  - GeneratedValue 어노테이션 : Id어노테이션이 선언된 필드에 기본 키를 자동으로 생성하여 할당할 때 사용
  - Temporal 어노테이션 : 날짜 타입의 변수에 선언하여 날짜 타입을 매핑할 때 사용
```
@Entity
@Table(name="BOARD")
public class Board implements Serializable {
	@Id
	@GeneratedValue
	private int seq;
	private String title;
	private String writer;
	private String content;
	@Temporal(TemporalType.DATE)
	private Date regDate = new Date();
	private int cnt;
	private static final long serialVersionUID = 1L;

	// getter and setter 
	...
}
```
- JPA 설정파일 properties 설정 (src/main/java/META-INF/persistence.xml)
  - 다음 클래스에서 자세히 설정
- 설정한 JPA를 사용하는 클라이언트 프로그램(클래스) 작성
