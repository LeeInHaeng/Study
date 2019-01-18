# Model 2 ��Ű����
- Model 1�� ��� �ڹ� ������ ȭ�� �������� ���յǾ� ���������� ��ƴ�.
- �̸� �ذ��ϱ� ���� Model 2�� MVC�� ���԰�, JSP�� �ƴ� ���� Ŭ������ �߽����� Controller�� �����ߴ�.
- ��, Model 1���� JSP ���Ͽ� �ִ� �ڹ� �ڵ常 Controller�� �̵��ϸ� Model 2�� �Ǵ� ���̴�.

# Controller ����
- new --> servlet, package : com.springbook.view.controller, class name : DispatcherServlet
- Name : action, /action ���� Ŭ�� �� Pattern�� "*.do"�� ����
- WEB-INF/web.xml ���� description ������Ʈ�� display-name ������Ʈ ����
- doGet() �޼ҵ忡 process(request, response); �� ����
- doPost() �޼ҵ忡 request.setCharacterEncoding("EUC-KR");  process(request, response); �� ����
- Ŭ���̾�Ʈ ��û URI�� ó���ϴ� process �޼ҵ� ����
```
	private void process(HttpServletRequest request, HttpServletResponse response) throws IOException{
		// 1. Ŭ���̾�Ʈ�� ��û path ������ ����
		String uri = request.getRequestURI();
		String path = uri.substring(uri.lastIndexOf("/"));
		System.out.println(path);
		
		// 2. Ŭ���̾�Ʈ�� ��û path�� ���� ������ �б�ó��
		if(path.equals("/login.do")) {
			System.out.println("�α��� ó��");
		}else if(path.equals("/logout.do")) {
			System.out.println("�α׾ƿ� ó��");
		}else if(path.equals("/insertBoard.do")) {
			System.out.println("�� ��� ó��");
		...
	}
```

# �ʱ� ����
- ���� ������ ó�� ����� JSP(View)�� �����ϱ� ���� HttpSession ��ü�� ���
  - �ش� ��ü�� ����ڰ� �������� ���� ������ �����ǰ�, ���� ������ ���� ����ɼ��� ���� ���忡���� �δ�
  - �ڵ� ����ȭ�� ���� HttpSession�� ��������� ���߿� Spring MVC������ HttpServletRequest�� ���
  - HttpServletRequest�� Ŭ���̾�Ʈ�� ������ ��û�� ������ ������ �Ź� ���Ӱ� �����Ǹ�, ���� �޽����� �������� ���۵Ǹ� �ٷ� �����Ǵ� 1ȸ�� ��ü�̹Ƿ� ������ �δ��� ���� �ʴ´�.
- JSP�� �ڹ� �ڵ�� �Ǿ��ִ� �κе��� �������� �ű����ν� _proc.jsp ������ ��� �����Ǿ���, jsp ������ view ��ɸ� ����.