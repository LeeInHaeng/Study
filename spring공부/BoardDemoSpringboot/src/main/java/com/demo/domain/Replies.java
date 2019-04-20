package com.demo.domain;

import java.util.Date;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

@Data
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class Replies {
	private long rid;
	private String content;
	private String writer;
	private Date regDate;
	private long recomCnt;
	private long fbid;
	private long groupId;
	private long pid;
}
