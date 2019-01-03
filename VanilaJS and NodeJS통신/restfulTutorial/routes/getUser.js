var express = require('express');
var router = express.Router();
var fs = require('fs');

/* GET home page. */
router.get('/:username', function(req, res, next) {
  fs.readFile(__dirname + "/../data/user.json","utf8",(err,data) => {
      var users = JSON.parse(data);
      res.json(users[req.params.username]);
  });
});

module.exports = router;