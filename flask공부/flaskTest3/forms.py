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