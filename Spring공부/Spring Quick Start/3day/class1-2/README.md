# Model 1 아키텍쳐 구조
- 90년대 말부터 2000년대 초반까지 사용
- client의 요청을 받는 container 안에 JSP(Controller+View)와 JavaBeans(Model)이 존재
- Model : 데이터베이스 연동 로직을 제공하면서 DB에서 검색한 데이터가 저장되는 자바 객체
- Controller : 사용자의 요청 처리와 관련된 자바 코드
  - 사용자 입력 정보 출력, DB 연동 처리, 화면 내비게이션
- View : 사용자가 원하는 화면을 제공하기 위한 마크업(HTML, CSS)을 사용
- Model 1은 마크업 코드와 자바 코드가 뒤섞여 있어서 디버깅과 유지보수에 어려움이 생긴다.

# http URL에 tomcat path 수정
- server 탭에서 톰캣 서버 더블클릭
- Modules 탭에서 Edit을 클릭 후 URL로 보이게 하고 싶은 path로 수정

# Model 1을 이용한 게시판 만들기
- src/main/webapp/.jsp 파일들
- getParameter() 을 이용해 사용자 정보를 추출한다.
- 이때 한글이 포함되어 있으면 추출 직전에 request.setCharacterEncoding("EUC-KR"); 을 이용해 인코딩 처리를 한다.
