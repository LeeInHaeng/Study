var express = require('express');
var router = express.Router();

router.post('/', function(req, res, next) {
  req.session.regenerate(function(){
      req.session.uid = req.body.user_id;
      req.session.pwd = req.body.user_pwd;

      res.render('myIndex', { title: 'MyIndex', uid: req.body.user_id, pwd: req.body.user_pwd,
                              session: JSON.stringify(req.session), suid: req.session.uid, spwd: req.session.pwd});

  });
});

module.exports = router;