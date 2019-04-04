using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace BoardDemo.Models
{
    public class Replies
    {
        public Int64 rid { get; set; }
        [StringLength(500)]
        public string content { get; set; }
        [StringLength(100)]
        public string writer { get; set; }
        public DateTime regDate { get; set; }
        public Int64 recomCnt { get; set; }
        public Int64 foreignBoard { get; set; }
        public Int64 groupId { get; set; }
        public Int64 pid { get; set; }
    }
}