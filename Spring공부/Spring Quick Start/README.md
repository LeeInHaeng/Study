# com.springbook.biz.board 패키지
- board와 관련된 VO 관련 클래스 모임 ( Value Object )
  - board와 관련된 private 변수들과, setter / getter 메소드들의 모임
- board와 관련된 Service 인터페이스
  - CRUD 기능의 메소드들이 선언되어 있는 인터페이스
# com.springbook.biz.board.impl 패키지
- board와 관련된 DAO 관련 클래스 모임 ( Data Access Object )
  - 실제로 데이터베이스에 질의하는 기능을 전담
- board와 관련된 ServiceImpl 클래스
  - Service 인터페이스를 구현한 클래스
  - CRUD 기능에 대해 DAO 클래스의 객체를 생성하여 DAO에 구현된 메소드를 수행
  - 유지보수를 위해 주로 사용되며, 사용하는 DAO 변경 시 해당 클래스의 변경만으로 간단한 유지보수가 가능
# com.springbook.biz.common 패키지
- 주로 AOP와 관련된 클래스들이 존재
# com.springbook.biz.user 패키지
- user와 관련된 VO 관련 클래스 모임 ( Value Object )
  - user와 관련된 private 변수들과, setter / getter 메소드들의 모임
- user와 관련된 Service 인터페이스
  - CRUD 기능의 메소드들이 선언되어 있는 인터페이스
# com.springbook.biz.user.impl 패키지
- user와 관련된 DAO 관련 클래스 모임 ( Data Access Object )
  - 실제로 데이터베이스에 질의하는 기능을 전담
- user와 관련된 ServiceImpl 클래스
  - Service 인터페이스를 구현한 클래스
  - CRUD 기능에 대해 DAO 클래스의 객체를 생성하여 DAO에 구현된 메소드를 수행
  - 유지보수를 위해 주로 사용되며, 사용하는 DAO 변경 시 해당 클래스의 변경만으로 간단한 유지보수가 가능
# com.springbook.view.board 패키지
- board와 관련된 컨트롤러 클래스 구현
  - 서비스 객체를 생성하고, 사용자의 요청에 따라 서비스 메소드 수행
  - 메소드 수행 후 사용자에게 보여줄 view를 return
# com.springbook.view.user 패키지
- user와 관련된 컨트롤러 클래스 구현
  - 로그인, 로그아웃 처리 등
# com.springbook.view.common 패키지
- 익셉션 핸들링을 위한 클래스 구현
  