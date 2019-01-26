# MyBatis Mapper XML 설정
- mapper을 루트 엘리먼트로 namespace를 사용하고, 그 아래에 select, insert 등의 엘리먼트를 두어 id를 설정한다.
  - 클래스에서 해당 Mapper를 사용하기 위해서 namespace.id로 접근을 할 수 있다
```
<mapper namespace="BoardDAO">
	<insert id="insertBoard">
		insert into board(seq, title, writer, content)
		values((select nvl(max(seq), 0)+1 from board), #{title}, #{writer}, #{content})
	</insert>
	...

// 클래스에서
	public void insertBoard(BoardVO vo) {
		mybatis.insert("BoardDAO.insertBoard",vo);
		mybatis.commit();
	}
```
- select 엘리먼트
  - resultType 속성 : SQL구문 실행 후 ResultSet이 리턴되며, 해당 검색 결과를 어떤 자바 객체에 매핑할지 지정
  - Mybatis 설정파일(sql-map-config.xml)에 alias 등록 후 mapping에 쉽게 객체를 등록할 수 있다.
```
// sql-map-config.xml
	<!-- Alias 설정 -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>

// board-mapping.xml
	<select id="getBoard" resultType="board">
		select * from board where seq=#{seq}
	</select>
```
- insert 엘리먼트
  - 자식 요소로 selectKey 엘리먼트를 가질 수 있다. 해당 엘리먼트를 통해 sql 질의를 하고, 그 결과를 insert 할 수 있다.
```
<insert id="insertBoard">
	<selectKey keyProperty="seq" resultType="int">
		select board_seq.nextval as seq from dual
	</selectKey>
	insert into board(seq, title, writer, content)
	values(#{seq}, #{title}, #{writer}, #{content})
</insert>
```
- update, delete 엘리먼트는 위의 엘리먼트드과 사용방법이 비슷하다.

- CDATA Section 사용 : 부등호 ( '<', '<=', '>', '>=' ) 등을 태그로 인식하기 때문에 에러가 발생
  - 문제 해결을 위해 CDATA Section으로 SQL 구문을 감싸준다.
```
<select id="getBoard" resultType"board">
	<! [CDATA[
	select * from board where seq <= #{seq}
	]]>
</select>
```

# SqlSession 객체 이용
- SqlSessionFactoryBean 클래스를 생성하여 SqlSession 객체를 얻기 위해 mybatis 설정 파일을 읽는다.
- mybatis 사용을 위해 SqlSession 객체를 불러온다.
```
	private SqlSession mybatis;
	
	public BoardDAO() {
		mybatis = SqlSessionFactoryBean.getSqlSessionInstance();
	}
```
- 해당 객체를 통해 insert, update, delete 등의 메소드를 사용할 수 있다.
- 검색 메소드 중 selectOne은 하나의 결과를 반환하는데 반환타입이 Object 이므로 형변환을 해준다.
```
	public BoardVO getBoard(BoardVO vo) {
		return (BoardVO) mybatis.selectOne("BoardDAO.getBoard",vo);
	}
```
- 검색 메소드 중 selectList는 List 형태로 결과를 반환한다.
```
	public List<BoardVO> getBoardList(BoardVO vo){
		return mybatis.selectList("BoardDAO.getBoardList",vo);
	}
```
- SqlSession 객체를 이용하기 위해 해당 클래스 파일들을 직접 만든 상태이지만, 나중에 Spring과 연동을 할 때는 직접 만들 필요가 없다.