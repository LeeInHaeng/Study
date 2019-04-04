using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

using BoardDemo.Models;
using BoardDemo.Models.Repository;

namespace BoardDemo.Controllers
{
    public class replController : Controller
    {
        private DapperReplRepository repo;
        private DapperBoardRepository repo2;

        public replController(DapperReplRepository repoParam, DapperBoardRepository repoParam2)
        {
            repo = repoParam;
            repo2 = repoParam2;
        }

        public PartialViewResult GetRepl(Int64 bid)
        {
            var data = repo.GetRepl(bid);
            if (data.Count() == 0)
            {
                Replies r = new Replies();
                r.foreignBoard = bid;
                List<Replies> list = new List<Replies>();
                list.Add(r);

                return PartialView(list);
            }

            return PartialView(data);
        }

        public PartialViewResult register(string replArea, Int64 bid)
        {
            repo2.AddRcnt(bid);

            Replies r = new Replies();
            r.content = replArea;
            r.writer = (string)Session["userId"];
            r.foreignBoard = bid;
            r.groupId = -1;
            r.pid = -1;
            repo.AddRepl(r);

            repo.UpdateReplGroupId(bid);

            var data = repo.GetRepl(bid); 
            return PartialView("GetRepl", data);
        }

        public PartialViewResult delete(Int64 rid)
        {
            int replParent = repo.GetReplParent(rid);

            repo.RemoveRepl(rid);
            repo2.decRcnt(replParent);

            var data = repo.GetRepl(replParent);
            return PartialView("GetRepl", data);
        }

        public PartialViewResult registerDap(string dapgleArea, Int64 bid, Int64 pid, Int64 groupId)
        {

            Replies r = new Replies();
            r.content = dapgleArea;
            r.writer = (string)Session["userId"];
            r.foreignBoard = bid;
            r.groupId = groupId;
            r.pid = pid;
            repo.AddRepl(r);

            var data = repo.GetRepl(bid);
            return PartialView("GetRepl", data);
        }
    }
}