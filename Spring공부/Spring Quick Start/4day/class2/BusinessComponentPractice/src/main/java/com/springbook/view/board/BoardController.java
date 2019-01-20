package com.springbook.view.board;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.SessionAttributes;

import com.springbook.biz.board.BoardVO;
import com.springbook.biz.board.impl.BoardDAO;

@Controller
@SessionAttributes("board")
public class BoardController {
	// �� ���
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo, BoardDAO boardDAO) {
		System.out.println("�� ��� ó��");
		
		boardDAO.insertBoard(vo);
		// return "getBoardList.do"; ---> ������ ���(URL�� ������� ����)
		return "redirect:getBoardList.do";
	}
	
	// �� ����
	@RequestMapping("/updateBoard.do")
	public String updateBoard(@ModelAttribute("board") BoardVO vo, BoardDAO boardDAO) {
		System.out.println("�� ���� ó��");
		
		boardDAO.updateBoard(vo);
		
		return "redirect:getBoardList.do";
	}
	
	// �� ����
	@RequestMapping("/deleteBoard.do")
	public String deleteBoard(BoardVO vo, BoardDAO boardDAO) {
		System.out.println("�� ���� ó��");
		
		boardDAO.deleteBoard(vo);
		
		return "redirect:getBoardList.do";
	}
	
	// �� �� ��ȸ
	@RequestMapping("/getBoard.do")
	public String getBoard(BoardVO vo, BoardDAO boardDAO, Model model) {
		System.out.println("�� �� ��ȸ ó��");

		model.addAttribute("board", boardDAO.getBoard(vo));
		return "getBoard.jsp";
	}
	
	// �� ��� �˻�
	@RequestMapping("/getBoardList.do")
	public String getBoardList(BoardVO vo, BoardDAO boardDAO, Model model) {
		System.out.println("�� ��� �˻� ó��");
		
		model.addAttribute("boardList", boardDAO.getBoardList(vo));
		return "getBoardList.jsp";
	}
}
