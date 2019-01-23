# 검색 기능 추가 구현
- SQL 문
```
private final String BOARD_LIST_T = "select * from board where title like '%'||?||'%' order by seq desc";
private final String BOARD_LIST_C = "select * from board where content like '%'||?||'%' order by seq desc";
```
- getBoardList 메소드 완성
```
		if(vo.getSearchCondition().equals("TITLE"))
			return jdbcTemplate.query(BOARD_LIST_T,args,new BoardRowMapper());
		else if(vo.getSearchCondition().equals("CONTENT"))
			return jdbcTemplate.query(BOARD_LIST_C,args,new BoardRowMapper());
```