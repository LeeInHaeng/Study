using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace BoardDemo
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: null,
                url: "{controller}/page{page}",
                defaults: new { controller = "board", action = "Index", category = (string)null },
                constraints: new { page = @"\d+" }
            );

            routes.MapRoute(
                name: null,
                url: "{controller}/{category}",
                defaults: new { controller = "board", action = "Index", page = 1 },
                constraints: new { category = "ALL|NOTICE" }
            );

            routes.MapRoute(
                name: null,
                url: "{controller}/{category}/page{page}",
                defaults: new { controller = "board", action = "Index" },
                constraints: new { category = "ALL|NOTICE", page = @"\d+" }
            );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{bid}",
                defaults: new { controller = "Home", action = "Index", bid = UrlParameter.Optional }
            );

            /*
            routes.MapRoute(
                name: "null",
                url: "{controller}/{action}/{rid}",
                defaults: new { controller = "repl", action = "GetRepl", rid = UrlParameter.Optional }
            );
            */
        }
    }
}
