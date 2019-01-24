# 데이터 교환 포맷으로 JSON 사용
- pom.xml에서 Jackson2 라이브러리 사용을 위해 dependency 추가
```
		<!-- Jackson2 -->
		<dependency>
			<groupId>com.fasterxml.jackson.core</groupId>
			<artifactId>jackson-databind</artifactId>
			<version>2.7.2</version>
		</dependency>
```
- 응답 결과를 HTML이 아닌 JSON이나 XML로 변환을 위해 Converter 사용
  - 스프링 설정파일(action-servlet.xml)에서 엘리먼트 추가
```
<mvc:annotation-driven></mvc:annotation-driven>
```
- Controller에서 처리 : ResponseBody 어노테이션 사용
  - 해당 어노테이션을 통해 JSON으로 변환되어 HTTP 응답 보디에 설정된다.
```
import java.util.List;
import org.springframework.web.bind.annotation.ResponseBody;

	@RequestMapping("/dataTransform.do")
	@ResponseBody
	public List<BoardVO> dataTransform(BoardVO vo){
		vo.setSearchCondition("TITLE");
		vo.setSearchKeyword("");
		List<BoardVO> boardList = boardService.getBoardList(vo);
		return boardList;
	}
```
- JSON 정보 중 출력 결과에 제외하기 위해서는 JsonIgnore 어노테이션 등록
  - BoardVO.java에서 검색 조건, 검색 키워드, 파일 업로드 정보는 제외
```
import com.fasterxml.jackson.annotation.JsonIgnore;

	@JsonIgnore
	public String getSearchCondition() {
		return searchCondition;
	}
	@JsonIgnore
	public String getSearchKeyword() {
		return searchKeyword;
	}
	@JsonIgnore
	public MultipartFile getUploadFile() {
		return uploadFile;
	}
```

# 데이터 교환 포맷으로 XML 사용
- BoardVO.java에서 XML로 변환할 변수들 지정
  - XmlAttribute 어노테이션을 통해 해당 변수를 속성으로 표현
  - XmlTransient 어노테이션을 통해 XML 변환에서 제외할 변수 등록
```
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlTransient;

@XmlAccessorType(XmlAccessType.FIELD)
public class BoardVO {
	@XmlAttribute
	private int seq;
	private String title;
	private String writer;
	private String content;
	private Date regDate;
	private int cnt;
	@XmlTransient
	private String searchCondition;
	@XmlTransient
	private String searchKeyword;
	@XmlTransient
	private MultipartFile uploadFile;
```
- 여러 게시글 목록을 XML로 표현하기 위해 BoardVO의 리스트 형태인 BoardListVO.java 클래스 생성
  - XmlRootElement 어노테이션을 통해 XML 전체의 root를 설정
  - XmlElement 어노테이션을 통해 root 엘리먼트의 하위 엘리먼트 이름을 설정
```
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "boardList")
@XmlAccessorType(XmlAccessType.FIELD)
public class BoardListVO {
	@XmlElement(name = "board")
	private List<BoardVO> boardList;
	
	public List<BoardVO> getBoardList(){
		return boardList;
	}
	
	public void setBoardList(List<BoardVO> boardList) {
		this.boardList = boardList;
	}
}

```
- Controller에서 처리 : ResponseBody 어노테이션 사용
  - 해당 어노테이션을 통해 XML로 변환되어 HTTP 응답 보디에 설정된다.
```
	@RequestMapping("/dataTransform.do")
	@ResponseBody
	public BoardListVO dataTransform(BoardVO vo){
		vo.setSearchCondition("TITLE");
		vo.setSearchKeyword("");
		List<BoardVO> boardList = boardService.getBoardList(vo);
		BoardListVO boardListVO = new BoardListVO();
		boardListVO.setBoardList(boardList);
		return boardListVO;
	}
```
