# 참고
- http://jinbroing.tistory.com/106

# npm 모듈
- npm install -g express-generator
- express --ejs 프로젝트명
- cd 프로젝트명
- npm install
- 서버 수행 : npm start

# 수행 동작
- 포트 등 설정 : bin/www
- 서버 동작 : app.js
- get, post 라우팅 설정, 보내줄 데이터 설정 : routes/index.js
- views : 다른 view include 가능
- localohst:3000/login (myLogin.ejs) 에서 id, pwd 입력 후 index (index.ejs)로 넘기기
- 넘어온 데이터들은 index.ejs의 input type hidden에 저장
- index.ejs의 javascript는 public/javascripts/index_script.ejs 에서 동작

# 다음 할 일
- input type hidden의 보안 문제로 session 구현