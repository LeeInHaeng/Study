from flask import Flask, render_template, request, make_response, redirect, url_for, session, flash
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.secret_key = 'any random string'
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024

@app.route("/")
def index():
    return render_template('student.html')

@app.route('/hello/<user>')
def hello_name(user):
   return render_template('hello.html', name = user)

@app.route('/result')
def result():
   dict = {'phy':50,'che':60,'maths':70}
   return render_template('result.html', result = dict)

@app.route('/multiResult', methods = ['POST', 'GET'])
def multiResult():
    if request.method == 'POST':
        result = request.form
        return render_template("multiResult.html", result = result)

@app.route('/setcookie', methods = ['POST', 'GET'])
def setcookie():
   if request.method == 'POST':
      user = request.form['nm']

      resp = make_response(redirect(url_for('readcookie')))
      resp.set_cookie('userID', user)

      return resp
   else:
      return render_template('cookieIndex.html')

@app.route('/readcookie')
def readcookie():
   userID = request.cookies.get('userID')
   return render_template('readcookie.html', userID = userID)

@app.route('/sessionLogin', methods = ['POST', 'GET'])
def sessionLogin():
   if request.method == 'POST':
      session['userID'] = request.form['nm']
      return redirect(url_for('sessionLoginSuccess'))
   else:
      return render_template('sessionLogin.html')

@app.route('/sessionLoginSuccess')
def sessionLoginSuccess():
   if 'userID' in session:
      userID = session['userID']
      return render_template('sessionLoginSuccess.html', userID = userID)
   else:
      return redirect(url_for('sessionLogin'))

@app.route('/sessionLogout')
def sessionLogout():
   session.pop('userID', None)
   return redirect(url_for('sessionLogin'))

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

@app.route('/upload', methods = ['POST', 'GET'])
def upload():
   if request.method == 'POST':
      f = request.files['myFile']
      #f.save('./uploader/' + secure_filename(f.filename))
      f.save('./uploader/' + f.filename)
      return 'file uploaded successfully'
   else:
      return render_template('upload.html')

if __name__ == "__main__":
    app.run()