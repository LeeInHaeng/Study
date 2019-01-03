var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
    var sess = req.session;
    if(sess.username){
        req.session.destroy(err => {
            if(err){
                console.log(err);
            }
            else{
                res.redirect('/');
            }
        });
    }
    else{
        res.redirect('/');
    }
});

module.exports = router;