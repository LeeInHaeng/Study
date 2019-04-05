# Templates
- Flask에서 제공하는 기본 Template 엔진인 Jinja2 사용
- python에서 render_template 함수 사용
  - hello.html을 렌더할 때 name 변수에 데이터를 받아서 템플릿에 넘겨준다.
```
from flask import Flask, render_template

@app.route('/hello/<user>')
def hello_name(user):
   return render_template('hello.html', name = user)
```
- 프로젝트에서 templates 폴더 생성 후 html 파일 생성
- ```{{ }}``` 안에 변수명을 통해 python에서 넘겨준 변수를 읽어올 수 있다.
  - templates/hello.html
```
<!doctype html>
<html>
   <body>
   
      <h1>Hello {{ name }}!</h1>
      
   </body>
</html>
```
- html에서 ```{% %}```을 통해 조건문, 반복문 등을 수행할 수 있다.
- 조건문 예제
  - if, elif, else, endif 사용
```
      {% if marks>50 %}
         <h1> Your result is pass!</h1>
      {% else %}
         <h1>Your result is fail</h1>
      {% endif %}
```
- 반복문 예제 (dictionary)
  - for, endfor 사용
  - loop.index : for 구분이 반복된 횟수 (1부터 세기 시작)
  - loop.index0 : for 구분이 반복된 횟수 (0부터 세기 시작)
  - loop.first : 반복이 처음일 경우 True, 아닐 경우 False
  - loop.last : 마지막 반복일 경우 True, 아닐 경우 False
  - loop.length : 전체 반복 횟수
  - loop.cycle('1','2','3') : 반복문이 돌 때마다 순서대로 1,2,3을 출력
```
// python
@app.route('/result')
def result():
   dict = {'phy':50,'che':60,'maths':70}
   return render_template('result.html', result = dict)

// html
<!doctype html>
<html>
   <body>
      <table border = 1>
         {% for key, value in result.items() %}
            <tr>
               <th> {{ key }} </th>
               <td> {{ value }} </td>
            </tr>
         {% endfor %}
      </table>
   </body>
</html>
```

# Static Files
- javascript나 CSS같은 정적 파일을 다루기 위한 방법
- static 디렉터리를 만들고 그 안에 정적 파일을 둔다.
  - static/hello.js
```
function sayHello() {
    alert("Hello World")
 }
```
- html에서 url_for을 이용해 정적 파일인 js를 불러온다.
```
<html>
   <head>
      <script type = "text/javascript" 
         src = "{{ url_for('static', filename = 'hello.js') }}" ></script>
   </head>
   
   <body>
      <input type = "button" onclick = "sayHello()" value = "Say Hello" />
   </body>
</html>
```

# Sending Form Data to Template
- html에서 form 태그로 전송되는 데이터가 많을 경우 python에서 request.form으로 데이터를 받는다.
- request.form으로 데이터를 받을 경우 dictionary 형태로 데이터가 들어온다.
  - input 박스의 name이 key로 되고, 그 안에 들어간 데이터가 value가 된다.
- python에서 request.form 사용
```
@app.route('/multiResult', methods = ['POST', 'GET'])
def multiResult():
    if request.method == 'POST':
        result = request.form
        return render_template("multiResult.html", result = result)
```
- form 태그에 다양한 데이터를 전송하는 student.html
```
<html>
   <body>
      <form action = "http://localhost:5000/multiResult" method = "POST">
         <p>Name <input type = "text" name = "Name" /></p>
         <p>Physics <input type = "text" name = "Physics" /></p>
         <p>Chemistry <input type = "text" name = "chemistry" /></p>
         <p>Maths <input type ="text" name = "Mathematics" /></p>
         <p><input type = "submit" value = "submit" /></p>
      </form>
   </body>
</html>
```
- 결과를 보여주는 multiResult.html
```
<!doctype html>
<html>
   <body>
      <table border = 1>
         {% for key, value in result.items() %}
            <tr>
               <th> {{ key }} </th>
               <td> {{ value }} </td>
            </tr>
         {% endfor %}
      </table>
   </body>
</html>
```

# Cookies
- form 태그를 이용해 다른 페이지로 쿠키값을 전달하기 위한 값 셋팅
  - cookieIndex.html
```
<html>
   <body>
      <form action = "/setcookie" method = "POST">
         <p><h3>Enter userID</h3></p>
         <p><input type = 'text' name = 'nm'/></p>
         <p><input type = 'submit' value = 'Login'/></p>
      </form>
   </body>
</html>
```
- 서버에서 쿠키값 셋팅 후 다른 페이지로 전달
  - make_response를 이용해 다른 html을 렌더 혹은 리다이렉트 하도록 response를 요청한다.
  - make_response의 결과에 set_cookie를 이용해 쿠키 값을 셋팅한다.
```
@app.route('/setcookie', methods = ['POST', 'GET'])
def setcookie():
   if request.method == 'POST':
      user = request.form['nm']

      resp = make_response(redirect(url_for('readcookie')))
      resp.set_cookie('userID', user)

      return resp
   else:
      return render_template('cookieIndex.html')
```
- 쿠키 값을 가져오는 방법은 request.cookies.get을 이용한다.
```
@app.route('/readcookie')
def readcookie():
   userID = request.cookies.get('userID')
   return render_template('readcookie.html', userID = userID)
```

# Sessions
- 세션을 사용하기 위해 먼저 서버에서 secret_key를 셋팅한다.
```
app = Flask(__name__)
app.secret_key = 'any random string'
```
- 세션을 셋팅하기 위해서 session['키 값'] 을 사용할 수 있다.
```
@app.route('/sessionLogin', methods = ['POST', 'GET'])
def sessionLogin():
   if request.method == 'POST':
      session['userID'] = request.form['nm']
      return redirect(url_for('sessionLoginSuccess'))
   else:
      return render_template('sessionLogin.html')
```
- 세션을 가져오는 방법 또한 session['키 값'] 을 이용해 가져온다.
- 또한 세션이 존재하는지 확인하기 위해 if '키 값' in session 조건을 사용할 수 있다.
```
@app.route('/sessionLoginSuccess')
def sessionLoginSuccess():
   if 'userID' in session:
      userID = session['userID']
      return render_template('sessionLoginSuccess.html', userID = userID)
   else:
      return redirect(url_for('sessionLogin'))
```
- 세션을 제거하기 위해서는 session.pop을 이용한다.
```
@app.route('/sessionLogout')
def sessionLogout():
   session.pop('userID', None)
   return redirect(url_for('sessionLogin'))
```

# Errors
- 플라스크에서 abort 메소드를 이용해 에러 페이지로 보낼 수 있다.
  - 400 : Bad Request
  - 401 : for Unauthenticated
  - 403 : for Forbidden
  - 404 : for Not Found ...
```
abort(401)
```

# Message Flashing
- flash 메소드를 이용해 서버에서 클라이언트로 메세지를 보낼 수 있다.
```
@app.route('/messageLogin', methods = ['POST', 'GET'])
def messageLogin():
   if request.method == 'POST':
      userID = request.form['nm']
      if userID != 'admin':
         flash('not admin')
         flash('multiple message')
         flash('asdasd')
         flash('testtest')
         return redirect(url_for('messageLogin'))
   else:
      return render_template('messageLogin.html')
```
- html에서 get_flashed_messages를 이용해 flash 메세지를 얻어올 수 있다.
- html에서 flash 존재 여부에 따라서 적절히 출력해준다.
```
        {% with messages = get_flashed_messages() %}
        {% if messages %}
            <ul>
            {% for message in messages %}
                <li>{{ message }}</li>
            {% endfor %}
           </ul>
        {% endif %}
        {% endwith %}
```

# File Uploading
- app.config[‘UPLOAD_FOLDER’] : 업로드 후 저장될 폴더 경로를 지정한다.
- app.config[‘MAX_CONTENT_PATH’] : 업로드할 수 있는 최대 크기를 지정한다 (바이트)
```
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
```
- 파일 업로드를 위해 클라이언트의 form태그의 enctype을 설정한다.
```
<html>
   <body>
      <form action = "http://localhost:5000/uploader" method = "POST" 
         enctype = "multipart/form-data">
         <input type = "file" name = "myFile" />
         <input type = "submit"/>
      </form>
   </body>
</html>
```
- 서버에서 파일을 받기 위해 request.files['input 태그의 name 속성'] 을 사용한다.
- save 메소드를 이용해 파일을 저장한다.
  - 이때 app.config[‘UPLOAD_FOLDER’]에서 경로 지정을 하지 않았다면 여기서 경로를 지정 한다.
- secure_filename을 사용하는 경우는 한글(utf-8)로 파일 명이 저장되기 때문에 주의
- secure_filename 사용 시 utf-8 인코딩 참고 사이트
  - http://www.voidcn.com/article/p-cxjdqemb-bpc.html
```
from werkzeug.utils import secure_filename

@app.route('/upload', methods = ['POST', 'GET'])
def upload():
   if request.method == 'POST':
      f = request.files['myFile']
      #f.save('./uploader/' + secure_filename(f.filename))
      f.save('./uploader/' + f.filename)
      return 'file uploaded successfully'
   else:
      return render_template('upload.html')
```
