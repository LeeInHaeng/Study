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

/*
/////////// get test /////////////
app.get('/login.html',function(req,res){
    //console.log(req.query);
    if(req.query.userid==='aaa' && req.query.userpass==='asd'){
        res.redirect('/success.html');
    }
    else{
        res.redirect('/failed.html');    
    } 
});
*/

/*
/////////// post test ////////////
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
*/

/*
/////////// db access test && Ajax ///////////////
app.use(bodyParser.urlencoded({ extended: true })); 
app.use(bodyParser.json());

const connection = mysql.createConnection({
    host: '127.0.0.1',
    user: 'root',
    password: '1234',
    port: 3307,
    // schema
    database: 'nodejstest'
});

app.post('/login.html',function(req,res){
    //console.log(req.body);
    let query = "insert into userinfo(userid,userpass) values(?,?)";
    let param = [req.body.userid, req.body.userpass];
    connection.query(query,param,function(err,row,field){
    if(!err){
        query = "select * from userinfo";
        connection.query(query,function(err,row,field){
            if(!err){
                res.send(row);
                //connection.end();
            }
            else
                console.log(err);
        });
    }
    else
        console.log(err);
    }); 
});
*/
