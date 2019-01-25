# Mybatis 장점
- 매우 짧은 자바 코드를 바탕으로 DB 연동 처리
- SQL 명령어를 자바 코드와 분리하여 XML 파일로 따로 관리
  - 이를 통해 SQL 명령어를 한 곳에 모아 통합 관리가 가능
- SQL 명령어 실행 결과를 자바 객체에 자동으로 매핑, 즉 데이터 맵퍼 기능을 제공

# Mybatis 연동
- Eclipse 마켓플레이스에서 Mybatis 관련 플러그인 설치
  - MyBatipse 1.2.1
- pom.xml에 사용할 DB와 Mybatis 관련 Dependency 추가
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
- 프로젝트에 MyBatis XML Mapper 추가
  - board-mapping.xml ---> src/main/resources/mappings에 이동

- mapper을 루트엘리먼트로 insert, update, delete, select 엘리먼트를 이용하여 SQL문 등록

- db.properties와 Mybatis 설정파일 추가 (현재 마켓플레이스에서 설치 에러 ---> 직접 작성)
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
	<!-- Properties 파일 설정 -->
	<properties resource="db.properties"/>
	
	<!-- Alias 설정 -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>
	
	<!-- DataSource 설정 -->
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
	
	<!-- Sql Mapper 설정 -->
	<mappers>
		<mapper resource="mappings/board-mapping.xml"/>
	</mappers>
</configuration>
```
- Mybatis를 이용하기 위해 SqlSession 객체가 필요
  - com.springbook.biz.util 패키지에 SqlSessionFactoryBean 클래스
  - Mybatis 설정파일을 읽어 SqlSessionFactory 객체를 생성
```
...
	Reader reader = Resources.getResourceAsReader("sql-map-config.xml");
	sessionFactory = new SqlSessionFactoryBuilder().build(reader);
```
- Mybatis를 이용하여 클래스 작성
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
