# �˻� ��� �߰� ����
- SQL ��
```
private final String BOARD_LIST_T = "select * from board where title like '%'||?||'%' order by seq desc";
private final String BOARD_LIST_C = "select * from board where content like '%'||?||'%' order by seq desc";
```
- getBoardList �޼ҵ� �ϼ�
```
		if(vo.getSearchCondition().equals("TITLE"))
			return jdbcTemplate.query(BOARD_LIST_T,args,new BoardRowMapper());
		else if(vo.getSearchCondition().equals("CONTENT"))
			return jdbcTemplate.query(BOARD_LIST_C,args,new BoardRowMapper());
```