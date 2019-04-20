package com.demo.repo;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.demo.domain.Replies;

@Mapper
public interface RepliesDAO {

	public void insertRepl(Replies r);
	
	public Replies getRepl(long rid);
	public List<Replies> getReplList();
	
	public void updateRepl(Replies r);
	
	public void deleteRepl(long r);
}
