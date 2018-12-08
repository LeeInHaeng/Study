# npm 모듈
- npm install -g express-generator
- express --ejs 프로젝트명
- cd 프로젝트명
- npm install
- 서버 수행 : npm start
- npm install express-session --save
- npm install socket.io --save

# 동작 방식
- 참고 : http://dalkomit.tistory.com/50
- ejsSession + socketio를 추가한 방식
- socketio 서버인 io.js 파일 생성, socketio 관련 이벤트들 작성
- bin/www 에서 io.js 호출
- node_modules에 있는 socket.io.js를 public/javascripts/socket.io.js 에 복사
- ejs에서 <script src="/javascripts/socket.io.js></script> 로 호출
- ejs에서 socketio 연결 (해당 예제는 logout.ejs에서 동작)
    
# ejs mysql 연동 시 참고 할 url
- https://dotblogs.com.tw/explooosion/2016/07/18/010601