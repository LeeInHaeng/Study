package com.demo.repo;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.demo.domain.Board;

@Mapper
public interface BoardDAO {

	public void insertBoard(Board b);
	
	public Board getBoard(long bid);
	public List<Board> getBoardList(String category);
	
	public void updateBoard(Board b);
	
	public void deleteBoard(long bid);
}
