# Mybatis ����
- �ſ� ª�� �ڹ� �ڵ带 �������� DB ���� ó��
- SQL ��ɾ �ڹ� �ڵ�� �и��Ͽ� XML ���Ϸ� ���� ����
  - �̸� ���� SQL ��ɾ �� ���� ��� ���� ������ ����
- SQL ��ɾ� ���� ����� �ڹ� ��ü�� �ڵ����� ����, �� ������ ���� ����� ����

# Mybatis ����
- Eclipse �����÷��̽����� Mybatis ���� �÷����� ��ġ
  - MyBatipse 1.2.1
- pom.xml�� ����� DB�� Mybatis ���� Dependency �߰�
```
		<!-- H2 Driver -->
		<dependency>
			<groupId>com.h2database</groupId>
			<artifactId>h2</artifactId>
			<version>1.4.197</version>
		</dependency>
		
		<!-- Mybatis -->
		<dependency>
			<groupId>org.mybatis</groupId>
			<artifactId>mybatis</artifactId>
			<version>3.3.1</version>
		</dependency>
		
		<!-- Ibatis -->
		<dependency>
			<groupId>org.apache.ibatis</groupId>
			<artifactId>ibatis-core</artifactId>
			<version>3.0</version>
		</dependency>
```
- ������Ʈ�� MyBatis XML Mapper �߰�
  - board-mapping.xml ---> src/main/resources/mappings�� �̵�

- mapper�� ��Ʈ������Ʈ�� insert, update, delete, select ������Ʈ�� �̿��Ͽ� SQL�� ���

- db.properties�� Mybatis �������� �߰� (���� �����÷��̽����� ��ġ ���� ---> ���� �ۼ�)
```
src/main/resource/db.properties

jdbc.driverClassName=org.h2.Driver
jdbc.url=jdbc:h2:tcp://localhost/~/test
jdbc.username=sa
jdbc.password=

src/main/resource/sql-map-config.xml

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
								"http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
	<!-- Properties ���� ���� -->
	<properties resource="db.properties"/>
	
	<!-- Alias ���� -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>
	
	<!-- DataSource ���� -->
	<environments default="development">
		<environment id="development">
			<transactionManager type="JDBC"/>
			<dataSource type="POOLED">
				<property name="driver" value="${jdbc.driverClassName}"/>
				<property name="url" value="${jdbc.url}"/>
				<property name="username" value="${jdbc.username}"/>
				<property name="password" value="${jdbc.password}"/>
			</dataSource>
		</environment>
	</environments>
	
	<!-- Sql Mapper ���� -->
	<mappers>
		<mapper resource="mappings/board-mapping.xml"/>
	</mappers>
</configuration>
```
- Mybatis�� �̿��ϱ� ���� SqlSession ��ü�� �ʿ�
  - com.springbook.biz.util ��Ű���� SqlSessionFactoryBean Ŭ����
  - Mybatis ���������� �о� SqlSessionFactory ��ü�� ����
```
...
	Reader reader = Resources.getResourceAsReader("sql-map-config.xml");
	sessionFactory = new SqlSessionFactoryBuilder().build(reader);
```
- Mybatis�� �̿��Ͽ� Ŭ���� �ۼ�
```
import org.apache.ibatis.session.SqlSession;
import com.springbook.biz.util.SqlSessionFactoryBean;

public class BoardDAO {
	private SqlSession mybatis;
	
	public BoardDAO() {
		mybatis = SqlSessionFactoryBean.getSqlSessionInstance();
	}
	
	public void insertBoard(BoardVO vo) {
		mybatis.insert("BoardDAO.insertBoard",vo);
		mybatis.commit();
	}
	...
}
```
