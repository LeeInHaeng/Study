var express = require('express');
var router = express.Router();
var fs = require('fs');

router.put('/:username', function(req, res, next) {
    var result = {};
    var username = req.params.username;

    // check req validity
    if(!req.body["password"] || !req.body["name"]){
        result["success"] = 0;
        result["error"] = "invalid request";
        res.json(result);
        return;
    }

    // load data and check duplication
    fs.readFile(__dirname + "/../data/user.json","utf8",(err,data) => {
        var users = JSON.parse(data);
        
        // not exist
        if(!users[username]){
            result["success"] = 0;
            result["error"] = "not exist";
            res.json(result);
            return;
        }

        // add to data
        users[username] = req.body;

        // save data
        fs.writeFile(__dirname + "/../data/user.json", JSON.stringify(users, null, '\t'), "utf8", (err,data) => {
            result["success"] = 1;
            res.json(result);
        });
  });
});

module.exports = router;