# 파일 업로드 처리
- form태그 수정 및 input type 추가
```
<form action="insertBoard.do" method="post" enctype="multipart/form-data">
...
		<tr>
			<td bgcolor="orange" width="70">업로드</td>
			<td align="left"><input type="file" name="uploadFile"/></td>
		</tr>
		...
```
- BoardVO에 파일과 관련된 변수 및 getter / setter 추가
```
import org.springframework.web.multipart.MultipartFile;

...
private MultipartFile uploadFile;
...
```
- pom.xml에 FileUpload 라이브러리를 받기 위해 dependency 추가
```
		<!-- FileUpload -->
		<dependency>
			<groupId>commons-fileupload</groupId>
			<artifactId>commons-fileupload</artifactId>
			<version>1.3.1</version>
		</dependency>
```
- 스프링 설정파일(action-servlet.xml)에 bean 등록
```
	<!-- 파일 업로드 설정 -->
	<bean id="multipartResolver" class="org.springframework.web.multipart.commons.CommonsMultipartResolver">
		<property name="maxUploadSize" value="100000" />
	</bean>
```
- Controller에서 파일 업로드에 관련된 처리를 한다.
```
import java.io.File;
import java.io.IOException;
import org.springframework.web.multipart.MultipartFile;

	// 글 등록
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) throws IOException {
		System.out.println("글 등록 처리");
		// 파일 업로드 처리
		MultipartFile uploadFile = vo.getUploadFile();
		if(!uploadFile.isEmpty()) {
			String fileName = uploadFile.getOriginalFilename();
			uploadFile.transferTo(new File("D:/" + fileName));
		}
		...
	}
```

# Controller에 일괄적 예외처리 (어노테이션 기반)
- 스프링 설정파일(action-servlet.xml)에 mvc 네임스페이스 추가 및 엘리먼트 설정
```
<mvc:annotation-driven></mvc:annotation-driven>
```
- 예외 처리를 담당하는 class 만들기
  - ControllerAdvice 어노테이션을 이용해 해당 패키지의 컨트롤러에서 예외가 발생하는 경우를 감지
  - ExceptionHandler 어노테이션을 이용해 어떤 예외가 발생했냐에 따라 해당 메소드들을 수행
```
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.servlet.ModelAndView;

@ControllerAdvice("com.springbook.view")
public class CommonExceptionHandler {

	@ExceptionHandler(ArithmeticException.class)
	public ModelAndView handlerArithmeticException(Exception e) {
		ModelAndView mav = new ModelAndView();
		mav.addObject("exception", e);
		mav.setViewName("/common/arithmeticError.jsp");
		return mav;
	}
	
	@ExceptionHandler(NullPointerException.class)
	public ModelAndView handleNullPointerException(Exception e) {
		ModelAndView mav = new ModelAndView();
		mav.addObject("exception",e);
		mav.setViewName("/common/nullPointerError.jsp");
		return mav;
	}
	...
}
```
- webapp/common/에 에러 view를 보여줄 jsp들 만들기
