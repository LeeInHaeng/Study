const express = require('express');
const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);
const fs = require('fs');
const mysql = require('mysql');
const bodyParser = require('body-parser');

app.use(express.static(__dirname+'/public'));

server.listen(3001, function() {
  console.log('Socket IO server listening on port 3001');
});

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

app.get('/success.html',function(req,res){
    res.sendFile(__dirname+'/success.html');
});

app.get('/failed.html',function(req,res){
    res.sendFile(__dirname+'/failed.html');
});

// get test
app.get('/login.html',function(req,res){
    //console.log(req.query);
    if(req.query.userid==='aaa' && req.query.userpass==='asd'){
        res.redirect('/success.html');
    }
    else{
        res.redirect('/failed.html');    
    } 
});

// post test
app.use(bodyParser.urlencoded({ extended: true })); 
app.use(bodyParser.json());

app.post('/login.html',function(req,res){
    //console.log(req.body);
    if(req.body.userid==='aaa' && req.body.userpass==='asd'){
        res.redirect('/success.html');
    }
    else{
        res.redirect('/failed.html');    
    } 
});