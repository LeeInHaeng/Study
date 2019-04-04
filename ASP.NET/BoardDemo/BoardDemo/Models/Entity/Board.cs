using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace BoardDemo.Models
{
    public class Board
    {
        public Int64 bid { get; set; }

        [StringLength(100, ErrorMessage = "제목의 최대 길이는 {1} 입니다.")]
        [Required(ErrorMessage = "제목을 입력해 주세요.")]
        [Display(Name = "제목")]
        public string title { get; set; }

        [StringLength(500, ErrorMessage = "제목의 최대 길이는 {1} 입니다.")]
        [Required(ErrorMessage = "내용을 입력해 주세요.")]
        [Display(Name = "내용")]
        public string content { get; set; }

        [StringLength(100)]
        [Display(Name = "작성자")]
        public string writer { get; set; }

        [Display(Name = "작성일")]
        public DateTime regDate { get; set; }

        [StringLength(20)]
        [Display(Name = "카테고리")]
        public string category { get; set; }

        public Int64 rCnt { get; set; }

        [Display(Name = "추천 수")]
        public Int64 recomCnt { get; set; }
    }
}