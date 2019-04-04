using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

using Dapper;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace BoardDemo.Models.Repository
{
    public class DapperBoardRepositoryImpl : DapperBoardRepository
    {
        private IDbConnection db = new SqlConnection(
            ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString);

        public Board DetailBoard(Int64 bid)
        {
            string sql = "SELECT * FROM dbo.Board WHERE bid = " + bid;
            return db.QueryFirstOrDefault<Board>(sql);
        }

        public void AddBoard(Board b)
        {
            string sql = "INSERT INTO dbo.Board(title, content, writer, category) " +
                "VALUES(N'" + b.title + "', N'" + b.content + "', N'" + b.writer + "', '" + b.category + "')";
            db.Query(sql);
        }

        public void EditBoard(Board b)
        {
            string sql = "UPDATE dbo.Board SET title = N'" + b.title + "', content = N'" + b.content +
                "', category = '" + b.category + "' WHERE bid = " + b.bid;
            db.Query(sql);
        }

        public IEnumerable<Board> GetBoard()
        {
            string sql = "SELECT * FROM dbo.Board ORDER BY bid DESC";
            return db.Query<Board>(sql);
        }

        public void RemoveBoard(Int64 bid)
        {
            string sql = "DELETE FROM dbo.Board WHERE bid = " + bid;
            db.Query(sql);
        }

        public void AddRcnt(Int64 bid)
        {
            string sql = "UPDATE dbo.Board SET rCnt = rCnt+1 WHERE bid = " + bid;
            db.Query(sql);
        }
        
        public void decRcnt(Int64 bid)
        {
            string sql = "UPDATE dbo.Board SET rCnt = rCnt-1 WHERE bid = " + bid;
            db.Query(sql);
        }
    }
}