var express = require('express');
var router = express.Router();

var redis = require('redis');
var rediscli = redis.createClient(6379,'127.0.0.1');
rediscli.on('error',err => {
  console.log(err);
});
// unique id generator
var uuidV4 = require('uuid/v4');

router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// GET ALL BOOKS
router.get('/api/books', function(req,res){
  rediscli.hgetall("books",(err,obj) => {
    if(err) return res.json({result: 0, error: err});
    if(obj) res.json(obj);
    else res.json({result: 0, error: 'not found books'});
  });
});

// GET SINGLE BOOK
router.get('/api/books/:book_id', function(req, res){
  var bookid = req.params.book_id;
  rediscli.hgetall("books",(err,obj) => {
    if(err) return res.json({result: 0, error: err});
    if(obj[bookid]) res.json(JSON.parse(obj[bookid]));
    else res.json({result: 0, error: 'not found book'});
  });
});

// GET BOOK BY AUTHOR
router.get('/api/books/author/:author', function(req, res){
  var author = req.params.author;
  var searchRes = {};
  rediscli.hgetall("books",(err,obj) => {
    if(err) return res.json({result: 0, error: err});
    Object.keys(obj).forEach(bookid => {
      var book = JSON.parse(obj[bookid]);
      if(book['author']===author)
        searchRes[bookid] = JSON.stringify(book);
    });
    if(Object.keys(searchRes).length==0)
    // return 안할 경우 error 발생?
      return res.json({result: 0, error: 'book not found'});
    res.json(searchRes);
  });
});

// CREATE BOOK
router.post('/api/books', function(req, res){
  if(req.body.title && req.body.author){
    var bookInfo = {};
    bookInfo.title = req.body.title;
    bookInfo.author = req.body.author;
    // date를 적지 않은 경우 현재 시간으로
    if(!req.body.published_date){
      var t = new Date();
      t.setHours(t.getHours()+9);
      bookInfo.date = t;
    }
    else{
      bookInfo.date = req.body.published_date;
    }
    rediscli.hset("books",uuidV4(),JSON.stringify(bookInfo));
    res.json({result: 1});
  }
  else
    res.json({result: 0, error: 'title or author not exist'});
});

// UPDATE THE BOOK
router.put('/api/books/:book_id', function(req, res){
  var bookid = req.params.book_id;
  rediscli.hgetall("books",(err,obj) => {
    if(err) return res.json({result: 0, error: err});
    if(obj[bookid]){
      var bookInfo = {};
      var tmpBook = JSON.parse(obj[bookid]);

      if(req.body.title) bookInfo.title = req.body.title;
      else bookInfo.title = tmpBook['title'];
      if(req.body.author) bookInfo.author = req.body.author;
      else bookInfo.author = tmpBook['author'];
      if(req.body.published_date) bookInfo.published_date = req.body.published_date;
      else bookInfo.published_date = tmpBook['published_date'];

      rediscli.hset("books",bookid,JSON.stringify(bookInfo));
      res.json({result: 1});
    }
    else res.json({result: 0, error: 'not found book'});
  });
});

// DELETE BOOK
router.delete('/api/books/:book_id', function(req, res){
  rediscli.hdel('books', req.params.book_id, (err,response) => {
    if(err) return res.json({result: 0, error: err});
    if(response) res.json({result: 1});
    else res.json({result: 0, error: 'not found book'});
  });
});

module.exports = router;
