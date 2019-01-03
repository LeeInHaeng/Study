# 강의 URL
- https://velopert.com/332

# 사용 모듈
- express --ejs
- npm install express-session --save
- 확장 프로그램 : Postman

# 동작 방식
- 사용자 정보 : data/user.json
- 모든 유저 리스트 출력(get) /list
- 특정 유저 정보 출력(get) /getUser/:username
- 새로운 유저 추가(post) /addUser/:username
- 유저 정보 변경(put) /updateUser/:username
- 유저 정보 삭제(delete) /deleteUser/:username
- 로그인(session 사용) /login/:username/:password
- 로그아웃(session destroy) /logout
