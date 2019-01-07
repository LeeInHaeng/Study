var Client = require('mariasql');
var c = new Client();

module.exports = function(){
    return {
        init: function() {
            return c.connect({
                host: '127.0.0.1',
                user: 'root',
                password: 'root',
                db: 'test'
            });
        },
        getMaria: function(){
            return c;
        }
    }
};