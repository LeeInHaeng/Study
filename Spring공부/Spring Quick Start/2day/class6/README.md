# JDBC ����� DB ����
- JDBC ����� DB ���� ���α׷��� ���� ������ �� �ֵ��� JdbcTemplate Ŭ������ ����
- �̸� ���� �����ڴ� �޶����� SQL ������ �������� �Ű� ���� �ȴ�.

# ������ JDBC ����
- pom.xml�� DBCP ���� dependency ������ �߰�
```
<!-- DBCP -->
<dependency>
	<groupId>commons-dbcp</groupId>
	<artifactId>commons-dbcp</artifactId>
	<version>1.4</version>
</dependency>
```
- pom.xml�� jdbc ��� ���� dependency ������ �߰�
```
<dependency>
	<groupId>org.springframework</groupId>
	<artifactId>spring-jdbc</artifactId>
	<version>${org.springframework-version}</version>
</dependency>
```
- ������Ƽ ������ Ȱ���� DataSource ���� (src/main/resources/config/database.properties)
```
jdbc.driver=org.h2.Driver
jdbc.url=jdbc:h2:tcp://localhost/~/test
jdbc.username=sa
jdbc.password=
```
- ��������.xml���� JdbcTemplate ��ü�� ����� DataSource�� <bean>�� ����Ѵ�.
```
<!-- DataSource ���� -->
<context:property-placeholder location="classpath:config/database.properties"/>
	 
<bean id="dataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
	<property name="driverClassName" value="${jdbc.driver}"/>
	<property name="url" value="${jdbc.url}"/>
	<property name="username" value="${jdbc.username}"/>
	<property name="password" value="${jdbc.password}"/>
</bean>
```
- JdbcTemplate Ŭ������ <bean>�� ����ϰ�, ������ �������� ó���Ͽ� ��� (��������.xml)
```
<!-- Spring JDBC ���� -->
<bean id="jdbcTemplate" class="org.springframework.jdbc.core.JdbcTemplate">
	<property name="dataSource" ref="dataSource" />
</bean>
```
- java ���Ͽ��� jdbcTemplate ���
  - import org.springframework.jdbc.core.JdbcTemplate;
```
@Autowired
private JdbcTemplate jdbcTemplate;

Object[] args = {vo.getTitle(), vo.getContent(), vo.getSeq()};
// (query, query�� ���õ� ����)
jdbcTemplate.update(BOARD_UPDATE,args);
```
- jdbcTemplate �� queryForObject�� select ������ ���� ����� �ڹ� ��ü�� �����Ͽ� ���Ϲ��� �� ��� (��� 1��)
- jdbcTemplate �� query�� queryForObject�� ���������� ����� 2�� �̻�
  - SQL ���� ���� �� �ڵ����� RowMapper ��ü�� mapRow() �޼ҵ带 ȣ��
```
// �� �� ��ȸ
public BoardVO getBoard(BoardVO vo) {
	System.out.println("===> Spring JDBC�� getBoard() ��� ó��");
	Object[] args = {vo.getSeq()};
	return jdbcTemplate.queryForObject(BOARD_GET, args, new BoardRowMapper());
}
	
// �� ��� ��ȸ
public List<BoardVO> getBoardList(BoardVO vo) {
	System.out.println("===> Spring JDBC�� getBoardList() ��� ó��");
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