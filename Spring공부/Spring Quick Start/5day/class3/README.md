# Spring MyBatis ����
- ���̺귯���� �����ޱ� ���� pom.xml�� dependency �߰�
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
- src/main/resources�� sql-map-config.xml�� mappings/�� board-mapping.xml �߰�
```
// sql-map-config.xml

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
								"http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
	<!-- Alias ���� -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>
	
	<!-- Sql Mapper ���� -->
	<mappers>
		<mapper resource="mappings/board-mapping.xml"/>
	</mappers>
</configuration>

// board-mapping.xml �״��
```
- ������ �������Ͽ� SqlSessionFactoryBean Ŭ������ Bean�� ��� (applicationContext.xml)
  - property�� ����� Database�� ������ �Ǿ��ִ� dataSource�� ���
  - property�� Mybatis ���������� xml ������ ���
```
	 <bean id="sqlSession" class="org.mybatis.spring.SqlSessionFactoryBean">
	 	<property name="dataSource" ref="dataSource" />
	 	<property name="configLocation" value="classpath:sql-map-config.xml" />
	 </bean>
```
- ������ �������Ͽ� SqlSessionTemplate Ŭ������ Bean�� ��� (applicationContext.xml)
```
	 <bean class="org.mybatis.spring.SqlSessionTemplate">
	 	<constructor-arg ref="sqlSession"></constructor-arg>
	 </bean>
```
- DAO Ŭ�������� Mybatis ���
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
		System.out.println("===> Mybatis�� getBoard ��� ó��");
		return (BoardVO) mybatis.selectOne("BoardDAO.getBoard",vo);
	}
	
	public List<BoardVO> getBoardList(BoardVO vo){
		System.out.println("===> Mybatis�� getBoardList ��� ó��");
		return mybatis.selectList("BoardDAO.getBoardList",vo);
	}
	...
}
```

# MyBatis mapping���� Dynamic SQL ����ϱ�
- mapping.xml ���� �� if ���� ���� ó���� �������� SQL���� ��Ʈ�� �� �� �ִ�. (board-mapping.xml)
  - ex) �������� �˻�, �������� �˻� �� SQL���� ���� ����ѵ� where ���Ǹ� �޶����Ƿ� �� �κ��� ����ó��
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