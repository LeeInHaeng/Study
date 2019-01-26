# JPA 설정파일
- persistence-unit 엘리먼트 : 루트 엘리먼트로 나중에 DAO 클래스 구현 시 사용할 name을 지정한다.
```
<persistence-unit name="JPAProject">
```
- class 엘리먼트 : Entity 클래스를 등록한다.
```
	<persistence-unit name="JPAProject">
		<class>com.springbook.biz.board.Board</class>
```
- 데이터베이스와 연동할 속성을 등록한다. 나중에 Spring과 연동시에는 DataSource를 등록해 놓기 때문에 해당 부분을 삭제한다.
```
	<persistence-unit name="JPAProject">
		<class>com.springbook.biz.board.Board</class>
		<properties>
			<!-- 필수 속성 -->
			<property name="javax.persistence.jdbc.driver" value="org.h2.Driver"/>
			<property name="javax.persistence.jdbc.user" value="sa" />
			<property name="javax.persistence.jdbc.password" value="" />
			<property name="javax.persistence.jdbc.url" value="jdbc:h2:tcp://localhost/~/test" />
```
- Dialect 클래스 : 해당 DBMS에 최적화된 SQL 구문을 생성해 준다.
  - 예제에서는 H2 데이터베이스를 사용하므로, 해당 데이터베이스의 Dialect를 설정한다.
  - DBMS 변경 시 Dialect 클래스만 변경하면 SQL이 자동으로 변경되어 생성되므로 유지보수가 크게 향상된다.
```
			<property name="hibernate.dialect" value="org.hibernate.dialect.H2Dialect" />
```
- 하이버네이트 관련 속성 설정
  - hibernate.show_sql : 생성된 SQL을 콘솔에 출력한다.
  - hibernate.format_sql : SQL을 출력할 때, 일정한 포맷으로 보기 좋게 출력한다.
  - hibernate.use_sql_comments : SQL에 포함된 주석도 같이 출력한다.
  - hibernate.id.new_generator_mappings : 새로운 키 생성 전략을 사용한다.
  - hibernate.hbm2ddl.auto : 테이블 생성이나 수정, 삭제 같은 DDL 구문을 자동으로 처리할지를 지정한다.
  - hibernate.hbm2ddl.auto 에서는 create, create-drop, update 속성이 있다.
  - create : 애플리케이션을 실행할 때, 기존 테이블을 삭제하고 새로운 테이블을 생성한다. (DROP --> CREATE)
  - create-drop : create와 같지만 애플리케이션이 종료되기 직전에 생성된 테이블을 삭제한다. (DROP --> CREATE --> DROP)
  - update : 기존에 사용 중인 테이블이 있으면 테이블을 생ㅅ엉하지 않고 재사용한다. 만약 엔티티 클래스의 매핑 설정이 변경되면 변경된 내용만 반영한다. (ALTER)
```
			<!-- 옵션 -->
			<property name="hibernate.show_sql" value="true" />
			<property name="hibernate.format_sql" value="true" />
			<property name="hibernate.use_sql_comments" value="false" />
			<property name="hibernate.id.new_generator_mappings" value="true" />
			<property name="hibernate.hbm2ddl.auto" value="create" />
```

# EntityManager 객체가 제공하는 CRUD 기능의 메소드들
- persist(Object entity) : 엔티티를 영속화한다. (INSERT)
- merge(Object entity) : 준영속 상태의 엔티티를 영속화한다. (UPDATE)
- remove(Object entity) : 영속 상태의 엔티티를 제거한다. (DELETE)
- find(Class<T> entityClass, Object primaryKey) : 하나의 엔티티를 검색한다. (SELECT ONE)
- createQuery(String qlString, class<T> resultClass) : JPQL에 해당하는 엔티티 목록을 검색한다. (SELECT LIST)