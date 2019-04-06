# Window10에서 Ubuntu 사용
- 개발자 모드 설정
  - 윈도우10 시작 ---> 개발자용 설정 검색 ---> 개발자 모드 선택
- Windows Subsystem for Linux 기능 활성화
  - 제어판 ---> 프로그램 및 기능 ---> Windows 기능 켜기/끄기 ---> Linux용 Windows 하위 시스템 체크
- 리눅스 배포판 선택 및 설치
  - Microsoft Store ---> linux 검색 ---> Ubuntu 다운 ---> 계정 설정
- Ubuntu home디렉토리 경로
  - C:\Users\lih\AppData\Local\Packages\CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc\LocalState\rootfs\home\lih

# 개발환경 virtulenv, flask, nginx
- sudo apt-get update
- sudo apt-get upgrade
- sudo apt-get install python3-pip python3-dev nginx
- sudo pip3 install virtualenv
- 프로젝트 디렉터리로 이동 후 'virtualenv 프로젝트명'
- source 프로젝트명/bin/activate
- virtualenv 상태에서는 pip3 명령어가 아닌 pip 명령어를 사용!
- pip install flask uwsgi
- 프로젝트에 들어간다.
- 가장 처음 보여줄 Hello.py 파일 생성
```
from flask import Flask
app = Flask(__name__)

@app.route("/")
def greeting():
        return "<h1 style='color:green'>Hello World!</h1>"

if __name__ == "__main__":
        app.run()
```
- wsgi.py 파일 생성
```
from Hello import app

if __name__ == "__main__":
    app.run()
```
- uwsgi.ini 파일 생성
```
[uwsgi]

module = wsgi

socket = myproject.sock
chmod-socket = 666
vacuum = true

daemonize = /home/lih/pythonTest/flaskTest/uwsgi.log

die-on-term = true
```
- uwsgi --ini uwsgi.ini
  - myproject.sock 파일이 생성된다.
- /etc/nginx/sites-available/flaskproject 파일 생성
```
server {
        listen 8080; (windows에서 ubuntu 사용하는 환경이기 때문에 80번 포트는 충돌)
        server_name localhost;
        location / { try_files $uri @app; }
        location @app {
                include uwsgi_params;
                uwsgi_pass unix:/home/lih/pythonTest/flaskTest/myproject.sock;
        }
}
```
- sudo ln -s /etc/nginx/sites-available/flaskproject /etc/nginx/sites-enabled/flaskproject
- sudo nginx -t (문법 체크)
- sudo service nginx restart

# Variable Rules
- ```< >``` 안에 받을 변수 명을 적고, 해당 변수 명을 def 인자로 받는다.
- 변수를 받을 때 타입을 지정할 수 있다.
```
@app.route('/hello/<name>')
def hello_name(name):
    return 'Hello %s!' % name

@app.route('/blog/<int:postID>')
def show_blog(postID):
    return 'Post Number %d' % postID

@app.route('/rev/<float:revNo>')
def revision(revNo):
    return 'Revision Number %f' % revNo
```
- localhost:5000/blog/hihi : hihi가 int형이 아니기 때문에 Not Found 발생
- localhost:5000/blog : 매개 변수가 없기 때문에 Not Found 발생

# URL Building
- url_for 함수를 이용해 URL을 특정 메소드에 맵핑할 수 있다.
- redirect와 url_for을 import 한다.
- 첫 번째 매개변수는 맵핑 시킬 함수 이름을 적는다.
- 두 번째 매개변수는 전달할 매개 변수를 적는다.
```
from flask import Flask, redirect, url_for

@app.route('/user/<name>')
def hello_user(name):
    if name =='admin':
        return redirect(url_for('hello_admin'))
    else:
        return redirect(url_for('hello_guest',guest = name))

@app.route('/admin')
def hello_admin():
    return 'Hello Admin'

@app.route('/guest/<guest>')
def hello_guest(guest):
    return 'Hello %s as Guest' % guest
```
- localhost:5000/user/admin 으로 접속 시 localhost:5000/admin 으로 연결
- localhost:5000/user/else 로 접속 시 http://localhost:5000/guest/else 로 연결

# HTTP Methods
- POST 테스트
  - localhost:5000/login에 post action 설정
  - input 박스의 name을 nm으로 설정하고 나중에 name을 이용해 python에서 변수로 받을 수 있다.
```
<html>
   <body>
      <form action = "http://localhost:5000/login" method = "post">
         <p>Enter Name:</p>
         <p><input type = "text" name = "nm" /></p>
         <p><input type = "submit" value = "submit" /></p>
      </form>
   </body>
</html>
```
- app.route에서 맵핑 URL과 methods를 설정할 수 있다.
- POST로 요청 받을 시 request.form['인풋에서 설정한 name'] 으로 받는다.
- GET으로 요청 시 request.args.get('인풋에서 설정한 name') 으로 받는다.
```
from flask import Flask, redirect, url_for, request

@app.route('/login',methods = ['POST', 'GET'])
def login():
   if request.method == 'POST':
      user = request.form['nm']
      return redirect(url_for('success',name = user))
   else:
      user = request.args.get('nm')
      return redirect(url_for('success',name = user))

@app.route('/success/<name>')
def success(name):
   return 'welcome %s' % name
```