package com.demo.controller;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

import javax.servlet.http.HttpServletRequest;
import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.support.PagedListHolder;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.demo.domain.Board;
import com.demo.domain.Replies;
import com.demo.repo.BoardDAO;
import com.demo.repo.RepliesDAO;

@Controller
public class BoardController {

	@Autowired
	private BoardDAO boardRepo;
	
	@Autowired
	private RepliesDAO replRepo;
	
	private PagedListHolder<Board> pagedList;
	private static final int PAGE_SIZE = 7;
	private static final int PAGE_CNT = 4;

	
	@RequestMapping(value="/board/{bid:[0-9]+}", method=RequestMethod.GET)
	public String getBoard(@PathVariable("bid") long bid,
			HttpServletRequest request,
			Model model) {
		Board b = boardRepo.getBoard(bid);
		
		model.addAttribute("board", b);
		model.addAttribute("oldURL", request.getHeader("referer"));
		return "board";
	}

	@RequestMapping(value="/board/{category:[a-zA-Z]+}", method=RequestMethod.GET)
	public String getBoardList(@PathVariable("category") String category, 
			Model model) {
		
		List<Board> boardList = boardRepo.getBoardList(category);
		
		pagedList = new PagedListHolder<Board>(boardList);
		pagedList.setPageSize(PAGE_SIZE);
		pagedList.setPage(0);
		
		model.addAttribute("boardList", pagedList);
		model.addAttribute("pageCnt", PAGE_CNT);
		model.addAttribute("category", category);
		
		return "boardList";
	}
	
	@RequestMapping(value="/board/insert", method=RequestMethod.GET)
	public String insertBoard(HttpServletRequest request,
			Model model) {
		
		Board b = new Board();
		
		//model.addAttribute("oldURL", request.getHeader("referer"));
		model.addAttribute("userID", "user00");
		model.addAttribute("board",b);

		return "boardInsert";
	}
	
	@RequestMapping(value="/board/insert", method=RequestMethod.POST)
	public String insertBoard(@Valid Board b, 
			BindingResult bindingResult,
			Model model) {
		
	    if (bindingResult.hasErrors()) {
	    	model.addAttribute("status","fail");
	    	model.addAttribute("board", b);
	    	model.addAttribute("userID",b.getWriter());
	    	return "boardInsert";
	    }
	    
	    boardRepo.insertBoard(b);
	    model.addAttribute("status","success");
	    return "redirect:/board/" + b.getCategory();
	}

	
	@RequestMapping(value= {"/board/{category}/page",
			"/board/{category}/page/{page}"}, method=RequestMethod.GET)
	public String getBoardListPage(@PathVariable("page") Optional<Integer> page,
			@PathVariable("category") String category,
			Model model) {
		
		int resPage = page.isPresent() ? page.get() : 1;
		resPage = resPage < 1 ? 1 : resPage;
		
		List<Board> boardList = boardRepo.getBoardList(category);
		
		pagedList = new PagedListHolder<Board>(boardList);
		pagedList.setPageSize(PAGE_SIZE);
		pagedList.setPage(resPage-1);
		
		resPage = resPage > pagedList.getPageCount() ? pagedList.getPageCount() : resPage;
		
		model.addAttribute("boardList", pagedList);
		model.addAttribute("pageCnt", PAGE_CNT);
		model.addAttribute("category",category);
		
		return "boardList";
	}

	@RequestMapping(value="/board/replies/insert", method=RequestMethod.POST)
	public ResponseEntity<Map> insertReplies(@RequestBody Replies r) {
		replRepo.insertRepl(r);
		Map<String, String> returnData = new HashMap<>();
		returnData.put("status", "success");
		
		return new ResponseEntity<>(returnData, HttpStatus.ACCEPTED);
	}

}
