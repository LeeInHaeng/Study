using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoardDemo.Models.Repository
{
    public interface DapperReplRepository
    {
        void AddRepl(Replies r);
        void EditRepl(Replies r);
        void RemoveRepl(Int64 rid);
        IEnumerable<Replies> GetRepl(Int64 bid);

        int GetReplParent(Int64 rid);
        void UpdateReplGroupId(Int64 bid);
    }
}
