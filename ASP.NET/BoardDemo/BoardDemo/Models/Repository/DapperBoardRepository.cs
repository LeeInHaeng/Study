using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoardDemo.Models.Repository
{
    public interface DapperBoardRepository
    {
        Board DetailBoard(Int64 bid);
        void AddBoard(Board b);
        void EditBoard(Board b);
        void RemoveBoard(Int64 bid);
        IEnumerable<Board> GetBoard();

        void AddRcnt(Int64 bid);
        void decRcnt(Int64 bid);
    }
}
