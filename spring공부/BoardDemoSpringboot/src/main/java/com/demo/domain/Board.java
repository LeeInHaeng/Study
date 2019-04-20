package com.demo.domain;

import java.util.Date;

import javax.validation.constraints.Size;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

@Data
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Board {
	private long bid;
	
	@Size(max=50, message="50글자 제약조건")
	private String title;
	
	private String content;
	private String writer;
	private Date regDate;
	private String category;
	private long rCnt;
	private long recomCnt;
}
