package com.springbook.view.user;

import javax.servlet.http.HttpSession;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import com.springbook.biz.user.UserVO;
import com.springbook.biz.user.impl.UserDAO;

@Controller
public class LoginController {
	@RequestMapping("/login.do")
	public String login(UserVO vo, UserDAO userDAO, HttpSession session) {
		System.out.println("로그인 처리");
		UserVO user = userDAO.getUser(vo);

		if(userDAO.getUser(vo) != null){
			session.setAttribute("userName", user.getName());
			return "redirect:getBoardList.do";
		}
		else{
			return "redirect:login.jsp";
		}
	}
}
