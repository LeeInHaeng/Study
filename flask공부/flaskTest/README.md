# Window10���� Ubuntu ���
- ������ ��� ����
  - ������10 ���� ---> �����ڿ� ���� �˻� ---> ������ ��� ����
- Windows Subsystem for Linux ��� Ȱ��ȭ
  - ������ ---> ���α׷� �� ��� ---> Windows ��� �ѱ�/���� ---> Linux�� Windows ���� �ý��� üũ
- ������ ������ ���� �� ��ġ
  - Microsoft Store ---> linux �˻� ---> Ubuntu �ٿ� ---> ���� ����
- Ubuntu home���丮 ���
  - C:\Users\lih\AppData\Local\Packages\CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc\LocalState\rootfs\home\lih

# ����ȯ�� virtulenv, flask, nginx
- sudo apt-get update
- sudo apt-get upgrade
- sudo apt-get install python3-pip python3-dev nginx
- sudo pip3 install virtualenv
- ������Ʈ ���͸��� �̵� �� 'virtualenv ������Ʈ��'
- source ������Ʈ��/bin/activate
- virtualenv ���¿����� pip3 ��ɾ �ƴ� pip ��ɾ ���!
- pip install flask uwsgi
- ������Ʈ�� ����.
- ���� ó�� ������ Hello.py ���� ����
```
from flask import Flask
app = Flask(__name__)

@app.route("/")
def greeting():
        return "<h1 style='color:green'>Hello World!</h1>"

if __name__ == "__main__":
        app.run()
```
- wsgi.py ���� ����
```
from Hello import app

if __name__ == "__main__":
    app.run()
```
- uwsgi.ini ���� ����
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
  - myproject.sock ������ �����ȴ�.
- /etc/nginx/sites-available/flaskproject ���� ����
```
server {
        listen 8080; (windows���� ubuntu ����ϴ� ȯ���̱� ������ 80�� ��Ʈ�� �浹)
        server_name localhost;
        location / { try_files $uri @app; }
        location @app {
                include uwsgi_params;
                uwsgi_pass unix:/home/lih/pythonTest/flaskTest/myproject.sock;
        }
}
```
- sudo ln -s /etc/nginx/sites-available/flaskproject /etc/nginx/sites-enabled/flaskproject
- sudo nginx -t (���� üũ)
- sudo service nginx restart

# Variable Rules
- ```< >``` �ȿ� ���� ���� ���� ����, �ش� ���� ���� def ���ڷ� �޴´�.
- ������ ���� �� Ÿ���� ������ �� �ִ�.
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
- localhost:5000/blog/hihi : hihi�� int���� �ƴϱ� ������ Not Found �߻�
- localhost:5000/blog : �Ű� ������ ���� ������ Not Found �߻�

# URL Building
- url_for �Լ��� �̿��� URL�� Ư�� �޼ҵ忡 ������ �� �ִ�.
- redirect�� url_for�� import �Ѵ�.
- ù ��° �Ű������� ���� ��ų �Լ� �̸��� ���´�.
- �� ��° �Ű������� ������ �Ű� ������ ���´�.
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
- localhost:5000/user/admin ���� ���� �� localhost:5000/admin ���� ����
- localhost:5000/user/else �� ���� �� http://localhost:5000/guest/else �� ����

# HTTP Methods
- POST �׽�Ʈ
  - localhost:5000/login�� post action ����
  - input �ڽ��� name�� nm���� �����ϰ� ���߿� name�� �̿��� python���� ������ ���� �� �ִ�.
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
- app.route���� ���� URL�� methods�� ������ �� �ִ�.
- POST�� ��û ���� �� request.form['��ǲ���� ������ name'] ���� �޴´�.
- GET���� ��û �� request.args.get('��ǲ���� ������ name') ���� �޴´�.
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