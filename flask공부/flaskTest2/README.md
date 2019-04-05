# Templates
- Flask���� �����ϴ� �⺻ Template ������ Jinja2 ���
- python���� render_template �Լ� ���
  - hello.html�� ������ �� name ������ �����͸� �޾Ƽ� ���ø��� �Ѱ��ش�.
```
from flask import Flask, render_template

@app.route('/hello/<user>')
def hello_name(user):
   return render_template('hello.html', name = user)
```
- ������Ʈ���� templates ���� ���� �� html ���� ����
- ```{{ }}``` �ȿ� �������� ���� python���� �Ѱ��� ������ �о�� �� �ִ�.
  - templates/hello.html
```
<!doctype html>
<html>
   <body>
   
      <h1>Hello {{ name }}!</h1>
      
   </body>
</html>
```
- html���� ```{% %}```�� ���� ���ǹ�, �ݺ��� ���� ������ �� �ִ�.
- ���ǹ� ����
  - if, elif, else, endif ���
```
      {% if marks>50 %}
         <h1> Your result is pass!</h1>
      {% else %}
         <h1>Your result is fail</h1>
      {% endif %}
```
- �ݺ��� ���� (dictionary)
  - for, endfor ���
  - loop.index : for ������ �ݺ��� Ƚ�� (1���� ���� ����)
  - loop.index0 : for ������ �ݺ��� Ƚ�� (0���� ���� ����)
  - loop.first : �ݺ��� ó���� ��� True, �ƴ� ��� False
  - loop.last : ������ �ݺ��� ��� True, �ƴ� ��� False
  - loop.length : ��ü �ݺ� Ƚ��
  - loop.cycle('1','2','3') : �ݺ����� �� ������ ������� 1,2,3�� ���
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
- javascript�� CSS���� ���� ������ �ٷ�� ���� ���
- static ���͸��� ����� �� �ȿ� ���� ������ �д�.
  - static/hello.js
```
function sayHello() {
    alert("Hello World")
 }
```
- html���� url_for�� �̿��� ���� ������ js�� �ҷ��´�.
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
- html���� form �±׷� ���۵Ǵ� �����Ͱ� ���� ��� python���� request.form���� �����͸� �޴´�.
- request.form���� �����͸� ���� ��� dictionary ���·� �����Ͱ� ���´�.
  - input �ڽ��� name�� key�� �ǰ�, �� �ȿ� �� �����Ͱ� value�� �ȴ�.
- python���� request.form ���
```
@app.route('/multiResult', methods = ['POST', 'GET'])
def multiResult():
    if request.method == 'POST':
        result = request.form
        return render_template("multiResult.html", result = result)
```
- form �±׿� �پ��� �����͸� �����ϴ� student.html
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
- ����� �����ִ� multiResult.html
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
- form �±׸� �̿��� �ٸ� �������� ��Ű���� �����ϱ� ���� �� ����
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
- �������� ��Ű�� ���� �� �ٸ� �������� ����
  - make_response�� �̿��� �ٸ� html�� ���� Ȥ�� �����̷�Ʈ �ϵ��� response�� ��û�Ѵ�.
  - make_response�� ����� set_cookie�� �̿��� ��Ű ���� �����Ѵ�.
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
- ��Ű ���� �������� ����� request.cookies.get�� �̿��Ѵ�.
```
@app.route('/readcookie')
def readcookie():
   userID = request.cookies.get('userID')
   return render_template('readcookie.html', userID = userID)
```

# Sessions
- ������ ����ϱ� ���� ���� �������� secret_key�� �����Ѵ�.
```
app = Flask(__name__)
app.secret_key = 'any random string'
```
- ������ �����ϱ� ���ؼ� session['Ű ��'] �� ����� �� �ִ�.
```
@app.route('/sessionLogin', methods = ['POST', 'GET'])
def sessionLogin():
   if request.method == 'POST':
      session['userID'] = request.form['nm']
      return redirect(url_for('sessionLoginSuccess'))
   else:
      return render_template('sessionLogin.html')
```
- ������ �������� ��� ���� session['Ű ��'] �� �̿��� �����´�.
- ���� ������ �����ϴ��� Ȯ���ϱ� ���� if 'Ű ��' in session ������ ����� �� �ִ�.
```
@app.route('/sessionLoginSuccess')
def sessionLoginSuccess():
   if 'userID' in session:
      userID = session['userID']
      return render_template('sessionLoginSuccess.html', userID = userID)
   else:
      return redirect(url_for('sessionLogin'))
```
- ������ �����ϱ� ���ؼ��� session.pop�� �̿��Ѵ�.
```
@app.route('/sessionLogout')
def sessionLogout():
   session.pop('userID', None)
   return redirect(url_for('sessionLogin'))
```

# Errors
- �ö�ũ���� abort �޼ҵ带 �̿��� ���� �������� ���� �� �ִ�.
  - 400 : Bad Request
  - 401 : for Unauthenticated
  - 403 : for Forbidden
  - 404 : for Not Found ...
```
abort(401)
```

# Message Flashing
- flash �޼ҵ带 �̿��� �������� Ŭ���̾�Ʈ�� �޼����� ���� �� �ִ�.
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
- html���� get_flashed_messages�� �̿��� flash �޼����� ���� �� �ִ�.
- html���� flash ���� ���ο� ���� ������ ������ش�.
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
- app.config[��UPLOAD_FOLDER��] : ���ε� �� ����� ���� ��θ� �����Ѵ�.
- app.config[��MAX_CONTENT_PATH��] : ���ε��� �� �ִ� �ִ� ũ�⸦ �����Ѵ� (����Ʈ)
```
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
```
- ���� ���ε带 ���� Ŭ���̾�Ʈ�� form�±��� enctype�� �����Ѵ�.
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
- �������� ������ �ޱ� ���� request.files['input �±��� name �Ӽ�'] �� ����Ѵ�.
- save �޼ҵ带 �̿��� ������ �����Ѵ�.
  - �̶� app.config[��UPLOAD_FOLDER��]���� ��� ������ ���� �ʾҴٸ� ���⼭ ��θ� ���� �Ѵ�.
- secure_filename�� ����ϴ� ���� �ѱ�(utf-8)�� ���� ���� ����Ǳ� ������ ����
- secure_filename ��� �� utf-8 ���ڵ� ���� ����Ʈ
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
