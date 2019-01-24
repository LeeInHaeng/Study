# ������ ��ȯ �������� JSON ���
- pom.xml���� Jackson2 ���̺귯�� ����� ���� dependency �߰�
```
		<!-- Jackson2 -->
		<dependency>
			<groupId>com.fasterxml.jackson.core</groupId>
			<artifactId>jackson-databind</artifactId>
			<version>2.7.2</version>
		</dependency>
```
- ���� ����� HTML�� �ƴ� JSON�̳� XML�� ��ȯ�� ���� Converter ���
  - ������ ��������(action-servlet.xml)���� ������Ʈ �߰�
```
<mvc:annotation-driven></mvc:annotation-driven>
```
- Controller���� ó�� : ResponseBody ������̼� ���
  - �ش� ������̼��� ���� JSON���� ��ȯ�Ǿ� HTTP ���� ���� �����ȴ�.
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
- JSON ���� �� ��� ����� �����ϱ� ���ؼ��� JsonIgnore ������̼� ���
  - BoardVO.java���� �˻� ����, �˻� Ű����, ���� ���ε� ������ ����
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

# ������ ��ȯ �������� XML ���
- BoardVO.java���� XML�� ��ȯ�� ������ ����
  - XmlAttribute ������̼��� ���� �ش� ������ �Ӽ����� ǥ��
  - XmlTransient ������̼��� ���� XML ��ȯ���� ������ ���� ���
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
- ���� �Խñ� ����� XML�� ǥ���ϱ� ���� BoardVO�� ����Ʈ ������ BoardListVO.java Ŭ���� ����
  - XmlRootElement ������̼��� ���� XML ��ü�� root�� ����
  - XmlElement ������̼��� ���� root ������Ʈ�� ���� ������Ʈ �̸��� ����
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
- Controller���� ó�� : ResponseBody ������̼� ���
  - �ش� ������̼��� ���� XML�� ��ȯ�Ǿ� HTTP ���� ���� �����ȴ�.
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
