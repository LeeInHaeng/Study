# WTF
- ���� ������ �������� form �ʵ带 ���� �� �ְ�, ��ȿ�� �˻縦 �� �� �ִ�.
- ���� ��ǲ �ʵ带 ���� �� CSRF ��ū�� ���� ������ֱ� ������ ���ȿ��� ����.
- pip install flask-WTF
- Form �ʵ� ��ҵ�
  - TextField : ```<input type='text'>```
  - BooleanField : ```<input type='checkbox'>```
  - DecimalField : TextField�� Decimal Ÿ���� ���� ��
  - IntegerField : TextField�� Integer Ÿ���� ���� ��
  - RadioField : ```<input type='radio'>
  - SelectField : ���� ���
  - TextAreaField : ```<textarea>```
  - PasswordField : ```<input type=password>```
  - SubmitField : ```<input type=submit>```
- Validator Ŭ���� ��ҵ�
  - InputRequired : ��ǲ �ʵ尡 ��� �ִ��� üũ
  - Email : ��ǲ �ʵ尡 �̸��� �������� üũ
  - IPAddress : ��ǲ �ʵ尡 IP �ּ� �������� üũ
  - Length : ��ǲ �ʵ� �������� ���̸� ����
  - NumberRange : ��ǲ �ʵ��� ���� ������ ����
  - URL : ��ǲ �ʵ尡 URL �������� üũ
- �� �±׸� ����� ���̽� ������ ���� �ۼ�
  - forms.py
  - �������� input �ڽ��� id�� name ��Ʈ����Ʈ�� ���� �ȴ�.
  - �� �ʵ��� ù ��° ���ڴ� label ������ ���õȴ�.
  - Radio�� Select ���� ������ �ʿ��� �ʵ�� choices�� �����Ѵ�. (value, ������ �̸�)
  - ��ȿ�� �˻�� ���ȣ �ȿ��ٰ� �����Ѵ�.
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
- ������ ������ ����.
  - ������ ������ forms.py���� ����� Ŭ������ import �Ѵ�.
  - csrf ��ū�� ���� secret_key�� �����ؾ� �Ѵ�.
  - Ŭ������ �����ϰ�, �ش� Ŭ������ ���ø��� �Ѱ��־� ����Ѵ�.
  - Ŭ����.validate()�� �̿��� ��ȿ�� �˻縦 �� �� �ִ�.
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
- html �ۼ��� ������ ����.
  - �����κ��� �Ѱ� ���� form Ŭ������ ����Ѵ�.
  - form.hidden_tag() �� �̿��� hidden Ÿ���� �� ���� ������ �� �ִ�.
  - csrf ��ū�� ���� �������� �ʾƵ� �ڵ����� form �±� �ȿ� ���� �ȴ�.
  - ������ form.������.label, form.������, form.������.name ������ ���� �����ϴ�.
  - Ư�� css�� ����� Ŭ������ ����ϱ� ���ؼ��� _class�� ����Ѵ�.
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
- �ö�ũ���� �⺻������ �����Ǵ� SQLite�� ���, ������ SQL�� ����� ���� ��
- ����� DB ����
  - connect �޼ҵ带 �̿��� database.db ��� �����ͺ��̽��� �����Ѵ�.
  - �ش� �޼ҵ�� database.db�� ���ٸ� ���� �����ϰ�, �ִٸ� ������ �����Ѵ�.
  - students ���̺��� �����.
```
import sqlite3

conn = sqlite3.connect('database.db')

conn.execute('CREATE TABLE students (name TEXT, addr TEXT, city TEXT, pin TEXT)')
conn.close()
```
- �������� �����ͺ��̽� ����ϱ� (������ ����)
  - sqlite3�� import �Ѵ�.
  - connect �޼ҵ带 �̿��� �����ͺ��̽��� �����Ѵ�.
  - �̶� with as �� �̿��� �ش� ���ῡ ��Ī�� ���δ�.
  - cursor �޼ҵ带 �̿��� ������ �����ϱ� ���� �۾��� �غ��Ѵ�.
  - cursor �޼ҵ带 ���� ������ ������ ���� execute �޼ҵ�� SQL ������ �����Ѵ�.
  - ���ۿ� �̻��� ���ٸ� commit�� �����Ѵ�.
  - ���ۿ� �̻��� ������ except �������� rollback�� �����Ѵ�.
  - �����ͺ��̽� ����� ������ close�� ���� ������ ���´�.
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
- �������� �����ͺ��̽� ����ϱ� (������ ��ȸ)
  - row_factory�� �����Ѵ�. �̷��� ������ ������ Į������ Ű������ �����͸� ��ȸ�� �� �ִ�.
  - cursor�� ���� SQL ������ �����Ѵ�.
  - ���� ����� fetchall�� ���� ����Ʈ ������ ����� ��� �̸� ���ø��� �Ѱ��ش�.
  - ���� �ϳ��� ������ fetchone�� ����Ѵ�.
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
- ���ø����� ����� �׷��ش�.
  - select ���� ����� row_factory�� ����߱� ������ �÷����� Ű������ �����Ϳ� ������ �� �ִ�.
```
         {% for row in rows %}
            <tr>
               <td>{{row["name"]}}</td>
		...
            </tr>
         {% endfor %}
```

# SQLAlchemy (ORM)
- https://www.tutorialspoint.com/flask/flask_sqlalchemy.htm ����

# Ajax
- Sijax ��� X
- Ŭ���̾�Ʈ���� jquery�� �̿��� Ajax ��û�� ������.
- ajaxSetup�� flask�� ��� Ajax��û�� ���� csrf ��ū�� ����ϱ� ���� ����
- ajax ���� �Ӽ� �� : success, error
- ajax �ۿ� �޼ҵ� : done, fail
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
- flask app�� ��ü������ csrf �� ���� CSRFProtect ����
- �������� ���� ó���� ���� jsonify�� ����Ѵ�.
  - Ŭ���̾�Ʈ���� �޴� �����ʹ� request.json['Ű ��'] ���� ���� �� �ִ�.
  - ��û�� ���� ������ jsonify�� �̿��� dictionary ������ �����͸� json ���·� �����Ѵ�.
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
