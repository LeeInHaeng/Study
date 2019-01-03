var express = require('express');
var router = express.Router();
var fs = require('fs');

router.get('/:username/:password', function(req, res, next) {
    var sess = req.session;
    fs.readFile(__dirname + "/../data/user.json","utf8",(err,data) => {
        var users = JSON.parse(data);
        var username = req.params.username;
        var password = req.params.password;
        var result = {};

        if(!users[username]){
            result["success"] = 0;
            result["error"] = "not found";
            res.json(result);
            return;
        }

        if(users[username]["password"] === password){
            result["success"] = 1;
            sess.username = username;
            sess.name = users[username]["name"];
            res.json(result);
        }
        else{
            result["success"] = 0;
            result["error"] = "incorrect password";
            res.json(result);
        }
    });
});

module.exports = router;