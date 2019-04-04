using BoardDemo.Models;
using BoardDemo.Models.Repository;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace BoardDemo.Controllers
{
    public class HomeController : Controller
    {
        /*
        private DapperBoardRepository repo; 

        public HomeController(DapperBoardRepository repoParam)
        {
            repo = repoParam;
        }
        */

        private DapperReplRepository repo;

        public HomeController(DapperReplRepository repoParam)
        {
            repo = repoParam;
        }

        public ActionResult Index()
        {
            /*
            // Board dummy data insert
            for (int i = 0; i < 99; i++)
            {
                Board b = new Board();
                b.title = "board title" + i;
                b.content = "board content" + i;
                b.writer = "user" + (i % 10);

                repo.AddBoard(b);
            }
            */

            /*
            // repl dummy data insert
            for(int i=0; i<10; i++)
            {
                Replies r = new Replies();
                r.content = "repl content!!!" + i;
                r.writer = "user" + (i % 3);
                r.foreignBoard = 112;
                r.groupId = i+1;
                r.pid = -1;

                repo.AddRepl(r);
            }
            */

            return View();
        }
    }
}