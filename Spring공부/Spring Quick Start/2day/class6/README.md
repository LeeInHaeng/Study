# JDBC 기반의 DB 연동
- JDBC 기반의 DB 연동 프로그램을 쉽게 개발할 수 있도록 JdbcTemplate 클래스를 지원
- 이를 통해 개발자는 달라지는 SQL 구문과 설정값만 신경 쓰면 된다.

# 스프링 JDBC 설정
- pom.xml에 DBCP 관련 dependency 설정을 추가
```
<!-- DBCP -->
<dependency>
	<groupId>commons-dbcp</groupId>
	<artifactId>commons-dbcp</artifactId>
	<version>1.4</version>
</dependency>
```
- pom.xml에 jdbc 모듈 관련 dependency 설정을 추가
```
<dependency>
	<groupId>org.springframework</groupId>
	<artifactId>spring-jdbc</artifactId>
	<version>${org.springframework-version}</version>
</dependency>
```
- 프로퍼티 파일을 활용한 DataSource 설정 (src/main/resources/config/database.properties)
```
jdbc.driver=org.h2.Driver
jdbc.url=jdbc:h2:tcp://localhost/~/test
jdbc.username=sa
jdbc.password=
```
- 설정파일.xml에서 JdbcTemplate 객체가 사용할 DataSource를 <bean>에 등록한다.
```
<!-- DataSource 설정 -->
<context:property-placeholder location="classpath:config/database.properties"/>
	 
<bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	<property name="driverClassName" value="${jdbc.driver}"/>
	<property name="url" value="${jdbc.url}"/>
	<property name="username" value="${jdbc.username}"/>
	<property name="password" value="${jdbc.password}"/>
</bean>
```
- JdbcTemplate 클래스를 <bean>에 등록하고, 의존성 주입으로 처리하여 사용 (설정파일.xml)
```
<!-- Spring JDBC 설정 -->
<bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
	<property name="dataSource" ref="dataSource" />
</bean>
```
- java 파일에서 jdbcTemplate 사용
  - import org.springframework.jdbc.core.JdbcTemplate;
```
@Autowired
private JdbcTemplate jdbcTemplate;

Object[] args = {vo.getTitle(), vo.getContent(), vo.getSeq()};
// (query, query에 관련된 인자)
jdbcTemplate.update(BOARD_UPDATE,args);
```
- jdbcTemplate 중 queryForObject는 select 구문의 실행 결과를 자바 객체로 매핑하여 리턴받을 때 사용 (결과 1개)
- jdbcTemplate 중 query는 queryForObject와 동일하지만 결과가 2개 이상
  - SQL 구문 수행 후 자동으로 RowMapper 객체의 mapRow() 메소드를 호출
```
// 글 상세 조회
public BoardVO getBoard(BoardVO vo) {
	System.out.println("===> Spring JDBC로 getBoard() 기능 처리");
	Object[] args = {vo.getSeq()};
	return jdbcTemplate.queryForObject(BOARD_GET, args, new BoardRowMapper());
}
	
// 글 목록 조회
public List<BoardVO> getBoardList(BoardVO vo) {
	System.out.println("===> Spring JDBC로 getBoardList() 기능 처리");
	return jdbcTemplate.query(BOARD_LIST, new BoardRowMapper());
}
```
```
class BoardRowMapper implements RowMapper<BoardVO>{
	public BoardVO mapRow(ResultSet rs, int rowNum) throws SQLException{
		BoardVO board = new BoardVO();
		board.setSeq(rs.getInt("SEQ"));
		...
		return board;
	}
}
```