from flask import Flask, request, render_template, jsonify
from forms import ContactForm
import sqlite3 as sql
from flask_wtf.csrf import CSRFProtect

app = Flask(__name__)
app.secret_key = 'development key'
csrf = CSRFProtect(app)

@app.route("/")
def greeting():
    return "<h1 style='color:green'>Hello World!</h1>"

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

@app.route('/enternew')
def new_student():
    return render_template('student.html')

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

@app.route('/list')
def list():
   con = sql.connect("database.db")
   con.row_factory = sql.Row
   
   cur = con.cursor()
   cur.execute("select * from students")
   
   rows = cur.fetchall()
   return render_template("list.html",rows = rows)

@app.route('/ajaxRequest', methods = ["POST","GET"])
def ajaxRequest():
    if request.method == "POST":
        reply = {'data1' : request.json['data1']+1, 'data2' : request.json['data2']+2}
        return jsonify(reply)
    else:
        return render_template("sijaxTest.html")

if __name__ == "__main__":
    app.run()