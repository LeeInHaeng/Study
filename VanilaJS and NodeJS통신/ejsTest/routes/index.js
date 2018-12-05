var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('myLogin',{title:'login'});
});

router.get('/login',function(req,res,next){
    res.render('myLogin',{title:'login'});
});

router.post('/login',function(req,res,next){
    const id = req.body.user_id;
    const pwd = req.body.user_pwd;
    const myJson = {
        test1: "hihi1",
        test2: "hihi2",
        test3: "hihi3"
    };
    res.render('index',{title:'Express', name:id, pwd:pwd, myJson:JSON.stringify(myJson)});
});

module.exports = router;
