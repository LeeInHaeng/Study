var express = require('express');
var router = express.Router();
var fs = require('fs');

router.delete('/:username', function(req, res, next) {
    var result = {};

    fs.readFile(__dirname + "/../data/user.json","utf8",(err,data) => {
        var users = JSON.parse(data);
        var username = req.params.username;
        
        // if not found
        if(!users[username]){
            result["success"] = 0;
            result["error"] = "not found";
            res.json(result);
            return;
        }

        delete users[username];

        // save data
        fs.writeFile(__dirname + "/../data/user.json", JSON.stringify(users, null, '\t'), "utf8", (err,data) => {
            result["success"] = 1;
            res.json(result);
            return;
        });
  });
});

module.exports = router;