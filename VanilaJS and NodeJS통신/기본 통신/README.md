Vanila Javascript ( not jquery )

# NodeJS 사용 모듈
- npm init
- npm install --save express
- npm install --save socket.io
- npm install --save fs
- npm install --save body-parser
- npm install --save mysql

# MySQL 인코딩 방식
- mysql Charset/Collation
- utf8mb4 / utf8mb4_unicode_ci

# MySQL Local 접속 시 Error 
- Message : Error: ER_NOT_SUPPORTED_AUTH_MODE: Client does not support authentication protocol requested - by server; consider upgrading MySQL client

- 해결 : ALTER USER ‘root’@’localhost’ IDENTIFIED WITH mysql_native_password BY ‘사용할패스워드’;

# 다음에 할 일
- 1) ejs를 이용해 동적 데이터 전달 html 만들기