# NodeJS + Restful + MariaDB Tutorial

# 필요 모듈
- npm install mariasql --save

# 설치 참고 URL
- https://downloads.mariadb.org/
- https://stackoverflow.com/questions/38217704/how-to-install-mariasql-with-nodejs-4-x-on-ubuntu-14
- http://lemontia.tistory.com/471

# NodeJS와 마리아DB 연동 참고 URL
- https://stackoverflow.com/questions/26350001/understanding-node-mariasql-example-code
- https://www.npmjs.com/package/mariasql
- mysql nodejs에서 구조화 예제
  - https://cheese10yun.github.io/mysql-node/
- mariadb id로 uuid 사용 예제
  - http://gafani.tistory.com/entry/MariaDBmysql-UUID-%EB%A1%9C-PK-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0
- mysql, mariadb default 현재 날짜
  - http://blog.makeajourney.kr/2016/07/26/mariadb-vs-mysql.html

# 동작 방식
- dbconnect.js에서 mariaDB connect 및 객체 반환
- index.js에서 반환된 객체를 이용하여 구현
- id는 binary16 uuid를 사용하므로 조건절 where에서 hex(id)로 조건 검사