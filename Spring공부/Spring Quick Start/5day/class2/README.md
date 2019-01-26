# MyBatis Mapper XML ����
- mapper�� ��Ʈ ������Ʈ�� namespace�� ����ϰ�, �� �Ʒ��� select, insert ���� ������Ʈ�� �ξ� id�� �����Ѵ�.
  - Ŭ�������� �ش� Mapper�� ����ϱ� ���ؼ� namespace.id�� ������ �� �� �ִ�
```
<mapper namespace="BoardDAO">
	<insert id="insertBoard">
		insert into board(seq, title, writer, content)
		values((select nvl(max(seq), 0)+1 from board), #{title}, #{writer}, #{content})
	</insert>
	...

// Ŭ��������
	public void insertBoard(BoardVO vo) {
		mybatis.insert("BoardDAO.insertBoard",vo);
		mybatis.commit();
	}
```
- select ������Ʈ
  - resultType �Ӽ� : SQL���� ���� �� ResultSet�� ���ϵǸ�, �ش� �˻� ����� � �ڹ� ��ü�� �������� ����
  - Mybatis ��������(sql-map-config.xml)�� alias ��� �� mapping�� ���� ��ü�� ����� �� �ִ�.
```
// sql-map-config.xml
	<!-- Alias ���� -->
	<typeAliases>
		<typeAlias alias="board" type="com.springbook.biz.board.BoardVO"/>
	</typeAliases>

// board-mapping.xml
	<select id="getBoard" resultType="board">
		select * from board where seq=#{seq}
	</select>
```
- insert ������Ʈ
  - �ڽ� ��ҷ� selectKey ������Ʈ�� ���� �� �ִ�. �ش� ������Ʈ�� ���� sql ���Ǹ� �ϰ�, �� ����� insert �� �� �ִ�.
```
<insert id="insertBoard">
	<selectKey keyProperty="seq" resultType="int">
		select board_seq.nextval as seq from dual
	</selectKey>
	insert into board(seq, title, writer, content)
	values(#{seq}, #{title}, #{writer}, #{content})
</insert>
```
- update, delete ������Ʈ�� ���� ������Ʈ��� ������� ����ϴ�.

- CDATA Section ��� : �ε�ȣ ( '<', '<=', '>', '>=' ) ���� �±׷� �ν��ϱ� ������ ������ �߻�
  - ���� �ذ��� ���� CDATA Section���� SQL ������ �����ش�.
```
<select id="getBoard" resultType"board">
	<! [CDATA[
	select * from board where seq <= #{seq}
	]]>
</select>
```

# SqlSession ��ü �̿�
- SqlSessionFactoryBean Ŭ������ �����Ͽ� SqlSession ��ü�� ��� ���� mybatis ���� ������ �д´�.
- mybatis ����� ���� SqlSession ��ü�� �ҷ��´�.
```
	private SqlSession mybatis;
	
	public BoardDAO() {
		mybatis = SqlSessionFactoryBean.getSqlSessionInstance();
	}
```
- �ش� ��ü�� ���� insert, update, delete ���� �޼ҵ带 ����� �� �ִ�.
- �˻� �޼ҵ� �� selectOne�� �ϳ��� ����� ��ȯ�ϴµ� ��ȯŸ���� Object �̹Ƿ� ����ȯ�� ���ش�.
```
	public BoardVO getBoard(BoardVO vo) {
		return (BoardVO) mybatis.selectOne("BoardDAO.getBoard",vo);
	}
```
- �˻� �޼ҵ� �� selectList�� List ���·� ����� ��ȯ�Ѵ�.
```
	public List<BoardVO> getBoardList(BoardVO vo){
		return mybatis.selectList("BoardDAO.getBoardList",vo);
	}
```
- SqlSession ��ü�� �̿��ϱ� ���� �ش� Ŭ���� ���ϵ��� ���� ���� ����������, ���߿� Spring�� ������ �� ���� ���� ���� �ʿ䰡 ����.