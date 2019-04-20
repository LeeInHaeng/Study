package com.demo;

import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.demo.domain.Board;
import com.demo.repo.BoardDAO;

@RunWith(SpringRunner.class)
@SpringBootTest
public class BoardDemoSpringbootApplicationTests {

    @Autowired
    private BoardDAO boardRepo;
	
	@Test
	public void contextLoads() {
	}

	/*
	@Test
	public void insertDummyBoard() {
		for(int i=100; i<120; i++) {
			Board b = new Board();
			b.setTitle("my board title"+i);
			b.setContent("this is board contents asdasd"+i);
			b.setWriter("user"+(i%10));
			b.setCategory("NOTICE");
			
			boardRepo.insertBoard(b);
		}
	}
	
	@Test
	public void getBoardList() {
		List<Board> boardList = boardRepo.getBoardList();
		for(Board b : boardList)
			System.out.println(b);
	}
	*/
	
}
