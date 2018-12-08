module.exports = function(server){
    var io = require('socket.io')(server);

    io.on('connection',function(socket){
        console.log('a user socketio connected');

        socket.on('disconnect',function(){
            console.log('user disconnected');
        });

        socket.on('logout socketio communication',function(data){
            socket.emit('logout socketio communication response','hihi client');
        });
    });
    return io;
}