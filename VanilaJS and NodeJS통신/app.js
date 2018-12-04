const express = require('express');
const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);
const fs = require('fs');
const mysql = require('mysql');
const bodyParser = require('body-parser');

app.use(express.static(__dirname+'/public'));

server.listen(3001, function() {
  console.log('http server listening on port 3001');
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

/*
/////////// socketio test ////////////

////// socketio message reference //////
 // sending to sender-client only
 //socket.emit('message', "this is a test");

 // sending to all clients, include sender
 //io.emit('message', "this is a test");

 // sending to all clients except sender
 //socket.broadcast.emit('message', "this is a test");

 // sending to all clients in 'game' room(channel) except sender
 //socket.broadcast.to('game').emit('message', 'nice game');

 // sending to all clients in 'game' room(channel), include sender
 //io.in('game').emit('message', 'cool game');

 // sending to sender client, only if they are in 'game' room(channel)
 //socket.to('game').emit('message', 'enjoy the game');

 // sending to all clients in namespace 'myNamespace', include sender
 //io.of('myNamespace').emit('message', 'gg');

 // sending to individual socketid
 //socket.broadcast.to(socketid).emit('message', 'for your eyes only');

io.on('connection', function(socket){
    console.log('user connected');
    
    socket.on('disconnect',function(){
        console.log('user disconnected');
        socket.disconnect();
    });
    
    socket.on('request database',function(data){
        console.log(data);
        const connection = mysql.createConnection({
            host: '127.0.0.1',
            user: 'root',
            password: '1234',
            port: 3307,
            // schema
            database: 'nodejstest'
        });
        let query = "select * from userinfo";
        connection.query(query,function(err,row,field){
            if(!err){
                socket.emit('database data',row);
            }
            else
                console.log(err);
        });
    });
});
*/
