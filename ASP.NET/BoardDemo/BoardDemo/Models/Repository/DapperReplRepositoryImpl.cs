using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;

using Dapper;

namespace BoardDemo.Models.Repository
{
    public class DapperReplRepositoryImpl : DapperReplRepository
    {
        private IDbConnection db = new SqlConnection(
            ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);

        public void AddRepl(Replies r)
        {
            string sql = "INSERT INTO dbo.Replies(content, writer, foreignBoard, groupId, pid) " +
                "VALUES(N'" + r.content + "', N'" + r.writer + "', " + r.foreignBoard + ", " +
                r.groupId + ", " + r.pid + ")";
            db.Query(sql);
        }

        public void EditRepl(Replies r)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Replies> GetRepl(Int64 bid)
        {
            string sql = "SELECT * FROM dbo.Replies WHERE foreignBoard = " + bid + " ORDER BY rid";
            return db.Query<Replies>(sql);
        }

        public void RemoveRepl(Int64 rid)
        {
            string sql = "DELETE FROM dbo.Replies WHERE rid = " + rid + " OR groupId = " + rid;
            db.Query(sql);
        }

        public void UpdateReplGroupId(Int64 bid)
        {
            string sql = "UPDATE dbo.Replies SET groupId = rid WHERE foreignBoard = " + bid + 
                " AND pid = -1";
            db.Query(sql);
        }

        public int GetReplParent(Int64 rid)
        {
            string sql = "SELECT foreignBoard FROM dbo.Replies WHERE rid = " + rid;
            return db.QueryFirstOrDefault<int>(sql);
        }
    }
}