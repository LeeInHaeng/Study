var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
    var preSession = JSON.stringify(req.session);
    req.session.destroy();
    res.render('logout', { title: 'myLogout', preSession: preSession,
                            curSession: JSON.stringify(req.session) });
});

module.exports = router;