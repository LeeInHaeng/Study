# npm 모듈
- npm install -g express-generator
- express --ejs 프로젝트명
- cd 프로젝트명
- npm install
- 서버 수행 : npm start
- npm install express-session --save

# 동작 방식
- app.js에서 session 옵션 설정
- 주의 : 옵션 설정 부분을 아래로 두면 미들웨어 문제로 인해 req.session이 undefined

- 처음 접속하면 app.js에서 '/' 경로 요청 ---> loginRouter의 login.js 호출
- login.js에서 login.ejs의 view를 보여줌

- login.ejs에서 myIndex로 post 요청
- app.js에서 '/myIndex' 경로 요청 ---> myIndexRouter의 myIndex.js 호출
- myIndex.js에서 myIndex.ejs의 view를 보여줌

- myIndex.ejs에서 myLogout으로 get 요청
- app.js에서 '/myLogout' 경로 요청 ---> myLogoutRouter의 myLogout.js 호출
- myLogout.js에서 logout.ejs의 view를 보여줌

- *주의 : 각각의 js에서 router.get 혹은 router.post 안의 경로는 모두 '/' 임.
- 만약 router 안에서 경로를 '/myIndex'로 적으면 '/myIndex/myIndex'가 되기 때문