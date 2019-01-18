# Model 2 아키텍쳐
- Model 1의 경우 자바 로직과 화면 디자인이 통합되어 유지보수가 어렵다.
- 이를 해결하기 위해 Model 2인 MVC가 나왔고, JSP가 아닌 서블릿 클래스를 중심으로 Controller가 등장했다.
- 즉, Model 1에서 JSP 파일에 있는 자바 코드만 Controller로 이동하면 Model 2가 되는 것이다.

# Controller 구현
- new --> servlet, package : com.springbook.view.controller, class name : DispatcherServlet
- Name : action, /action 더블 클릭 후 Pattern을 "*.do"로 설정
- WEB-INF/web.xml 에서 description 엘리먼트와 display-name 엘리먼트 삭제
- doGet() 메소드에 process(request, response); 로 수정
- doPost() 메소드에 request.setCharacterEncoding("EUC-KR");  process(request, response); 로 수정
- 클라이언트 요청 URI를 처리하는 process 메소드 구현
```
	private void process(HttpServletRequest request, HttpServletResponse response) throws IOException{
		// 1. 클라이언트의 요청 path 정보를 추출
		String uri = request.getRequestURI();
		String path = uri.substring(uri.lastIndexOf("/"));
		System.out.println(path);
		
		// 2. 클라이언트의 요청 path에 따라 적절히 분기처리
		if(path.equals("/login.do")) {
			System.out.println("로그인 처리");
		}else if(path.equals("/logout.do")) {
			System.out.println("로그아웃 처리");
		}else if(path.equals("/insertBoard.do")) {
			System.out.println("글 등록 처리");
		...
	}
```

# 필기 사항
- 서블릿 에서의 처리 결과를 JSP(View)와 공유하기 위해 HttpSession 객체를 사용
  - 해당 객체는 사용자가 많을수록 많은 세션이 생성되고, 세션 정보가 많이 저장될수록 서버 입장에서는 부담
  - 코드 간결화를 위해 HttpSession을 사용하지만 나중에 Spring MVC에서는 HttpServletRequest를 사용
  - HttpServletRequest는 클라이언트가 서버에 요청을 전송할 때마다 매번 새롭게 생성되며, 응답 메시지가 브라우저에 전송되면 바로 삭제되는 1회성 객체이므로 서버에 부담이 되지 않는다.
- JSP에 자바 코드로 되어있는 부분들을 서블릿으로 옮김으로써 _proc.jsp 파일은 모두 삭제되었고, jsp 파일은 view 기능만 남음.