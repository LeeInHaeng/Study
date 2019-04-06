# WTF
- 서버 측에서 동적으로 form 필드를 만들 수 있고, 유효성 검사를 할 수 있다.
- 또한 인풋 필드를 만들 때 CSRF 토큰을 같이 만들어주기 때문에 보안에도 좋다.
- pip install flask-WTF
- Form 필드 요소들
  - TextField : ```<input type='text'>```
  - BooleanField : ```<input type='checkbox'>```
  - DecimalField : TextField에 Decimal 타입을 위한 것
  - IntegerField : TextField에 Integer 타입을 위한 것
  - RadioField : ```<input type='radio'>
  - SelectField : 선택 양식
  - TextAreaField : ```<textarea>```
  - PasswordField : ```<input type=password>```
  - SubmitField : ```<input type=submit>```
- Validator 클래스 요소들
  - InputRequired : 인풋 필드가 비어 있는지 체크
  - Email : 인풋 필드가 이메일 형식인지 체크
  - IPAddress : 인풋 필드가 IP 주소 형식인지 체크
  - Length : 인풋 필드 데이터의 길이를 제한
  - NumberRange : 인풋 필드의 숫자 범위를 제한
  - URL : 인풋 필드가 URL 형식인지 체크
- 폼 태그를 만드는 파이썬 파일을 따로 작성
  - forms.py
  - 변수명이 input 박스의 id와 name 어트리뷰트에 셋팅 된다.
  - 각 필드의 첫 번째 인자는 label 값으로 셋팅된다.
  - Radio나 Select 같은 선택이 필요한 필드는 choices를 셋팅한다. (value, 보여줄 이름)
  - 유효성 검사는 대괄호 안에다가 선언한다.
```
from flask_wtf import FlaskForm
from wtforms import TextField, RadioField, TextAreaField, IntegerField, SelectField, SubmitField
from wtforms.validators import InputRequired, Email

class ContactForm(FlaskForm):
    name = TextField("Name Of Student", [InputRequired("Please enter your name.")])
    Gender = RadioField('Gender', choices = [('M','Male'),('F','Female')])
    Address = TextAreaField("Address")
   
    email = TextField("Email", [InputRequired("Please enter your email address."), Email("Please enter your email address.")])
   
    Age = IntegerField("age")
    language = SelectField('Languages', choices = [('cpp', 'C++'), ('py', 'Python')])
    submit = SubmitField("Send")
```
- 서버는 다음과 같다.
  - 위에서 선언한 forms.py에서 사용할 클래스를 import 한다.
  - csrf 토큰을 위해 secret_key를 설정해야 한다.
  - 클래스를 선언하고, 해당 클래스를 템플릿에 넘겨주어 사용한다.
  - 클래스.validate()를 이용해 유효성 검사를 할 수 있다.
```
from forms import ContactForm

app.secret_key = 'development key'

@app.route('/contact', methods = ['GET', 'POST'])
def contact():
    form = ContactForm()
    
    if request.method == 'POST':
        if form.validate() == False:
            return render_template('contact.html', form = form)
        else:
            return "success!"
    else:
        return render_template('contact.html', form = form)
```
- html 작성은 다음과 같다.
  - 서버로부터 넘겨 받은 form 클래스를 사용한다.
  - form.hidden_tag() 를 이용해 hidden 타입을 한 번에 설정할 수 있다.
  - csrf 토큰은 따로 지정하지 않아도 자동으로 form 태그 안에 설정 된다.
  - 선언한 form.변수명.label, form.변수명, form.변수명.name 등으로 접근 가능하다.
  - 특정 css가 적용된 클래스를 사용하기 위해서는 _class를 사용한다.
  - ex ) {{ form.email(class_="form-control") }}
```
<!doctype html>
<html>
   <body>
      <h2 style = "text-align: center;">Contact Form</h2>
		
      {% for message in form.name.errors %}
         <div>{{ message }}</div>
      {% endfor %}
      
      {% for message in form.email.errors %}
         <div>{{ message }}</div>
      {% endfor %}
      
      <form action = "{{ url_for('contact') }}" method = post>
         <fieldset>
            <legend>Contact Form</legend>
            {{ form.hidden_tag() }}
            
            <div style = font-size:20px; font-weight:bold; margin-left:150px;>
               {{ form.name.label }}<br>
               {{ form.name }}
               <br>
               
               {{ form.Gender.label }} {{ form.Gender }}

		...

               {{ form.submit }}
            </div>
            
         </fieldset>
      </form>
   </body>
</html>
```

# SQLite
- 플라스크에서 기본적으로 제공되는 SQLite를 사용, 순수한 SQL문 사용을 위한 것
- 사용할 DB 생성
  - connect 메소드를 이용해 database.db 라는 데이터베이스를 생성한다.
  - 해당 메소드는 database.db가 없다면 새로 생성하고, 있다면 연결을 수행한다.
  - students 테이블을 만든다.
```
import sqlite3

conn = sqlite3.connect('database.db')

conn.execute('CREATE TABLE students (name TEXT, addr TEXT, city TEXT, pin TEXT)')
conn.close()
```
- 서버에서 데이터베이스 사용하기 (데이터 삽입)
  - sqlite3를 import 한다.
  - connect 메소드를 이용해 데이터베이스에 접속한다.
  - 이때 with as 를 이용해 해당 연결에 별칭을 붙인다.
  - cursor 메소드를 이용해 쿼리를 수행하기 위한 작업을 준비한다.
  - cursor 메소드를 통해 생성한 변수를 통해 execute 메소드로 SQL 쿼리를 수행한다.
  - 동작에 이상이 없다면 commit을 수행한다.
  - 동작에 이상이 있으면 except 구문에서 rollback을 수행한다.
  - 데이터베이스 사용이 끝나면 close를 통해 연결을 끊는다.
```
import sqlite3 as sql

@app.route('/addrec',methods = ['POST', 'GET'])
def addrec():
    if request.method == 'POST':
        try:
            nm = request.form['nm']
            addr = request.form['add']
            city = request.form['city']
            pin = request.form['pin']
         
            with sql.connect("database.db") as con:
                cur = con.cursor()
                cur.execute("INSERT INTO students (name,addr,city,pin) VALUES (?,?,?,?)",(nm,addr,city,pin) )
            
                con.commit()
                msg = "Record successfully added"
                
        except:
            con.rollback()
            msg = "error in insert operation"
      
        finally:
            con.close()
            return render_template("result.html",msg = msg)     
```
- 서버에서 데이터베이스 사용하기 (데이터 조회)
  - row_factory를 선언한다. 이러한 선언의 장점은 칼럼명을 키값으로 데이터를 조회할 수 있다.
  - cursor을 통해 SQL 쿼리를 수행한다.
  - 쿼리 결과를 fetchall을 통해 리스트 형태의 결과를 얻고 이를 템플릿에 넘겨준다.
  - 만약 하나의 결과라면 fetchone을 사용한다.
```
@app.route('/list')
def list():
   con = sql.connect("database.db")
   con.row_factory = sql.Row
   
   cur = con.cursor()
   cur.execute("select * from students")
   
   rows = cur.fetchall()
   return render_template("list.html",rows = rows)
```
- 템플릿에서 결과를 그려준다.
  - select 구문 수행시 row_factory를 사용했기 때문에 컬럼명을 키값으로 데이터에 접근할 수 있다.
```
         {% for row in rows %}
            <tr>
               <td>{{row["name"]}}</td>
		...
            </tr>
         {% endfor %}
```

# SQLAlchemy (ORM)
- https://www.tutorialspoint.com/flask/flask_sqlalchemy.htm 참고

# Ajax
- Sijax 사용 X
- 클라이언트에서 jquery를 이용해 Ajax 요청을 보낸다.
- ajaxSetup은 flask에 모든 Ajax요청에 대해 csrf 토큰을 사용하기 위한 셋팅
- ajax 내부 속성 값 : success, error
- ajax 밖에 메소드 : done, fail
```
            $(document).ready(() => {

                var csrf_token = "{{ csrf_token() }}";
                console.log(csrf_token);

                $.ajaxSetup({
                    beforeSend: function(xhr, settings) {
                        if (!/^(GET|HEAD|OPTIONS|TRACE)$/i.test(settings.type) && !this.crossDomain) {
                            xhr.setRequestHeader("X-CSRFToken", csrf_token);
                        }
                    }
                });

                var data = {data1 : 1, data2 : 2};
                $('#addReply').click(() => {
                    $.ajax({
                        type: "POST",
                        url: "{{ url_for('ajaxRequest') }}",
                        data: JSON.stringify(data),
                        dataType: "json",
                        contentType: "application/json; charset=UTF-8"
                    })
                    .done(reply => {
                        console.log(reply);
                        $("#replyContainer").append("<p>"+reply["data1"]+"</p>");
                        $("#replyContainer").append("<p>"+reply["data2"]+"</p>");
                    });
                });
            });
```
- flask app에 전체적으로 csrf 방어를 위해 CSRFProtect 셋팅
- 서버에서 응답 처리를 위해 jsonify를 사용한다.
  - 클라이언트에서 받는 데이터는 request.json['키 값'] 으로 받을 수 있다.
  - 요청에 대한 응답은 jsonify를 이용해 dictionary 형태의 데이터를 json 형태로 리턴한다.
```
from flask import jsonify
from flask_wtf.csrf import CSRFProtect

app = Flask(__name__)
app.secret_key = 'development key'
csrf = CSRFProtect(app)

@app.route('/ajaxRequest', methods = ["POST","GET"])
def ajaxRequest():
    if request.method == "POST":
        reply = {'data1' : request.json['data1']+1, 'data2' : request.json['data2']+2}
        return jsonify(reply)
    else:
        return render_template("sijaxTest.html")
```
