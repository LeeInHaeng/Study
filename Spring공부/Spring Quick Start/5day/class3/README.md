# Spring MyBatis 연동
- 라이브러리를 내려받기 위해 pom.xml에 dependency 추가
```
		<!-- Mybatis -->
		<dependency>
			<groupId>org.mybatis</groupId>
			<artifactId>mybatis</artifactId>
			<version>3.3.1</version>
		</dependency>
		<!-- Mybatis Spring -->
		<dependency>
			<groupId>org.mybatis</groupId>
			<artifactId>mybatis-spring</artifactId>
			<version>1.2.4</version>
		</dependency>
```
- src/main/resources에 sql-map-config.xml과 mappings/에 board-mapping.xml 추가
```
// sql-map-config.xml

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
								"http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
	<!-- Alias 설정 -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>
	
	<!-- Sql Mapper 설정 -->
	<mappers>
		<mapper resource="mappings/board-mapping.xml"/>
	</mappers>
</configuration>

// board-mapping.xml 그대로
```
- 스프링 설정파일에 SqlSessionFactoryBean 클래스를 Bean에 등록 (applicationContext.xml)
  - property로 사용할 Database의 설정이 되어있는 dataSource를 등록
  - property로 Mybatis 설정파일인 xml 파일을 등록
```
	 <bean id="sqlSession" class="org.mybatis.spring.SqlSessionFactoryBean">
	 	<property name="dataSource" ref="dataSource" />
	 	<property name="configLocation" value="classpath:sql-map-config.xml" />
	 </bean>
```
- 스프링 설정파일에 SqlSessionTemplate 클래스를 Bean에 등록 (applicationContext.xml)
```
	 <bean class="org.mybatis.spring.SqlSessionTemplate">
	 	<constructor-arg ref="sqlSession"></constructor-arg>
	 </bean>
```
- DAO 클래스에서 Mybatis 사용
```
import java.util.List;

import org.mybatis.spring.SqlSessionTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

@Repository
public class BoardDAOMybatis {
	@Autowired
	private SqlSessionTemplate mybatis;

	public BoardVO getBoard(BoardVO vo) {
		System.out.println("===> Mybatis로 getBoard 기능 처리");
		return (BoardVO) mybatis.selectOne("BoardDAO.getBoard",vo);
	}
	
	public List<BoardVO> getBoardList(BoardVO vo){
		System.out.println("===> Mybatis로 getBoardList 기능 처리");
		return mybatis.selectList("BoardDAO.getBoardList",vo);
	}
	...
}
```

# MyBatis mapping에서 Dynamic SQL 사용하기
- mapping.xml 설정 시 if 같은 조건 처리를 바탕으로 SQL문을 컨트롤 할 수 있다. (board-mapping.xml)
  - ex) 제목으로 검색, 내용으로 검색 시 SQL문이 거의 비슷한데 where 조건만 달라지므로 이 부분을 조건처리
```
	<select id="getBoardList" resultType="board">
		select * from board
		where 1=1
		<if test="searchCondition == 'TITLE'">
			and title like '%'||#{searchKeyword}||'%'
		</if>
		<if test="searchCondition == 'CONTENT'">
			and content like '%'||#{searchKeyword}||'%'
		</if>
		order by seq desc
	</select>
```