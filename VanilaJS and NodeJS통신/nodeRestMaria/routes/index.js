var express = require('express');
var router = express.Router();
var conn = require('../dbconnect')();
conn.init();
var maria = conn.getMaria();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

// GET ALL BOOKS
router.get('/api/books', function(req,res){
  var query = maria.query('select hex(id), title, author, published_date from books');
  var viewRes = [];
  query.on('result', queryRes => {
    queryRes.on('data', row => {
      viewRes.push(row);
    }).on('end', () => {
      if(viewRes.length!=0) res.json(viewRes);
      else return res.status(404).json({result: 0, error: 'not found book'});
    }).on('error', err => {
      return res.status(500).json({result: 0, error: err});
    });
  });
});

// GET SINGLE BOOK
router.get('/api/books/:book_id', function(req, res){
  var prep = maria.prepare('select hex(id), title, author, published_date from books where hex(id)=:id');
  var viewRes;
  maria.query(prep({id: req.params.book_id}))
  .on('result', queryRes => {
    queryRes.on('data', row => {
      viewRes = row;
    })
    .on('end', () => {
      if(viewRes) res.json(viewRes);
      else return res.status(404).json({result: 0, error: 'not found book'});
    })
    .on('error', err => {
      return res.status(500).json({result: 0, error: err});
    });
  });
});

// GET BOOK BY AUTHOR
router.get('/api/books/author/:author', function(req, res){
  var prep = maria.prepare('select hex(id), title, author, published_date from books where author=:author');
  var viewRes = [];
  maria.query(prep({author: req.params.author}))
  .on('result', queryRes => {
    queryRes.on('data', row => {
      viewRes.push(row);
    })
    .on('end', () => {
      if(viewRes.length!=0) res.json(viewRes);
      else return res.status(404).json({result: 0, error: 'not found book'});
    })
    .on('error', err => {
      return res.status(500).json({result: 0, error: err});
    });
  });
});

// CREATE BOOK
router.post('/api/books', function(req, res){
  if(req.body.title && req.body.author){
    if(req.body.published_date){
      var prep = maria.prepare("insert into books (id,title,author,published_date) values (UNHEX(REPLACE(UUID(),'-','')),:title,:author,:published_date)");
      maria.query(prep({title: req.body.title, author: req.body.author, published_date: req.body.published_date}))
      .on('result',queryRes => {
        queryRes.on('end', () => {
          res.json({result: 1});
        })
        .on('error', err => {
          return res.status(500).json({result: 0, error: err});
        });
      });
    }
    else{
      var prep = maria.prepare("insert into books (id,title,author) values (UNHEX(REPLACE(UUID(),'-','')),:title,:author)");
      maria.query(prep({title: req.body.title, author: req.body.author}))
      .on('result',queryRes => {
        queryRes.on('end', () => {
          res.json({result: 1});
        })
        .on('error', err => {
          return res.status(500).json({result: 0, error: err});
        });
      });
    }
  }
  else
    res.json({result: 0, error: 'input title and author'});
});

// UPDATE THE BOOK
router.put('/api/books/:book_id', function(req, res){
  var prep = maria.prepare('select hex(id), title, author, published_date from books where hex(id)=:id');
  var viewRes;
  maria.query(prep({id: req.params.book_id}))
  .on('result', queryRes => {
    queryRes.on('data', row => {
      viewRes = row;
    })
    .on('end', () => {
      if(viewRes){
        var updateData = {};
        if(req.body.title) updateData.title = req.body.title;
        else updateData.title = viewRes.title;

        if(req.body.author) updateData.author = req.body.author;
        else updateData.author = viewRes.author;

        if(req.body.published_date) updateData.published_date = req.body.published_date;
        else updateData.published_date = viewRes.published_date;

        prep = maria.prepare('update books set title=:title, author=:author, published_date=:published_date where hex(id)=:id');
        maria.query(prep({title: updateData.title, author: updateData.author, published_date: updateData.published_date, id: req.params.book_id}))
        .on('result', queryRes2 => {
          queryRes2.on('end', () => {
            res.json({result: 1});
          })
          .on('error', err => {
            return res.status(500).json({result: 0, error: err});
          });
        });
      }
      else return res.status(404).json({result: 0, error: 'not found book'});
    })
    .on('error', err => {
      return res.status(500).json({result: 0, error: err});
    });
  });
});

// DELETE BOOK
router.delete('/api/books/:book_id', function(req, res){
  var prep = maria.prepare('delete from books where hex(id)=:id');
  maria.query(prep({id: req.params.book_id}))
  .on('result', queryRes => {
    queryRes.on('end', () => {
      res.json({result: 1});
    })
    .on('error', err => {
      return res.status(500).json({result: 0, error: err});
    });
  });
});

module.exports = router;
