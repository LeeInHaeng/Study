var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  var sess = req.session;

  res.render('index',{
    title: 'My HOMEPAGE',
    length: 5,
    name: sess.name,
    username: sess.username
  });
});

module.exports = router;
