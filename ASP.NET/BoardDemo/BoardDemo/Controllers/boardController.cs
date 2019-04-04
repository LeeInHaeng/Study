using BoardDemo.Models.Repository;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

using PagedList;
using BoardDemo.Models;

namespace BoardDemo.Controllers
{
    public class boardController : Controller
    {
        private DapperBoardRepository repo;
        private DapperReplRepository repoRepl;
        private int pageSize;

        public boardController(DapperBoardRepository repoParam, DapperReplRepository repoReplParam)
        {
            repo = repoParam;
            repoRepl = repoReplParam;
            pageSize = 10;
        }

        public ActionResult Index(string category, int? page)
        {
            int pageNo = page ?? 1;
            var viewData = repo.GetBoard()
                .Where(b => b.category == category || category == null);
            ViewBag.category = category ?? null;

            // tmp authorize
            Session["userId"] = "user0000";

            return View(viewData.ToPagedList(pageNo, pageSize));
        }

        [HttpGet]
        public ActionResult register()
        {
            Board b = new Board();
            b.writer = (string)Session["userId"];
            b.category = "ALL";
            return View(b);
        }

        [HttpPost]
        public ActionResult register(Board b)
        {
            if (ModelState.IsValid)
            {
                repo.AddBoard(b);
                TempData["result"] = "registerSuccess";
                return RedirectToAction("Index");
            }
            else
                return View();    
        }

        public ActionResult detail(Int64 bid)
        {
            return View(repo.DetailBoard(bid));
        }

        [HttpGet]
        public ActionResult edit(Int64 bid)
        {
            return View(repo.DetailBoard(bid));
        }

        [HttpPut]
        public ActionResult edit(Board b)
        {
            if (ModelState.IsValid)
            {
                repo.EditBoard(b);
                TempData["result"] = "editSuccess";
                return RedirectToAction("Index");
            }
            else
                return View();
        }

        public ActionResult delete(Int64 bid)
        {
            repo.RemoveBoard(bid);
            TempData["result"] = "deleteSuccess";
            return RedirectToAction("Index");
        }
    }
}