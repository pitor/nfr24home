var express = require('express');
var router = express.Router();
var radio  = require( __dirname + '/../libs/radio' );

/* GET home page. */
router.get('/vals', function(req, res, next) {
    res.json({ radio : radio.values()});
});

module.exports = router;
