# ���� ���ε� ó��
- form�±� ���� �� input type �߰�
```
<form action="insertBoard.do" method="post" enctype="multipart/form-data">
...
		<tr>
			<td bgcolor="orange" width="70">���ε�</td>
			<td align="left"><input type="file" name="uploadFile"/></td>
		</tr>
		...
```
- BoardVO�� ���ϰ� ���õ� ���� �� getter / setter �߰�
```
import org.springframework.web.multipart.MultipartFile;

...
private MultipartFile uploadFile;
...
```
- pom.xml�� FileUpload ���̺귯���� �ޱ� ���� dependency �߰�
```
		<!-- FileUpload -->
		<dependency>
			<groupId>commons-fileupload</groupId>
			<artifactId>commons-fileupload</artifactId>
			<version>1.3.1</version>
		</dependency>
```
- ������ ��������(action-servlet.xml)�� bean ���
```
	<!-- ���� ���ε� ���� -->
	<bean id="multipartResolver" class="org.springframework.web.multipart.commons.CommonsMultipartResolver">
		<property name="maxUploadSize" value="100000" />
	</bean>
```
- Controller���� ���� ���ε忡 ���õ� ó���� �Ѵ�.
```
import java.io.File;
import java.io.IOException;
import org.springframework.web.multipart.MultipartFile;

	// �� ���
	@RequestMapping(value="/insertBoard.do")
	public String insertBoard(BoardVO vo) throws IOException {
		System.out.println("�� ��� ó��");
		// ���� ���ε� ó��
		MultipartFile uploadFile = vo.getUploadFile();
		if(!uploadFile.isEmpty()) {
			String fileName = uploadFile.getOriginalFilename();
			uploadFile.transferTo(new File("D:/" + fileName));
		}
		...
	}
```

# Controller�� �ϰ��� ����ó�� (������̼� ���)
- ������ ��������(action-servlet.xml)�� mvc ���ӽ����̽� �߰� �� ������Ʈ ����
```
<mvc:annotation-driven></mvc:annotation-driven>
```
- ���� ó���� ����ϴ� class �����
  - ControllerAdvice ������̼��� �̿��� �ش� ��Ű���� ��Ʈ�ѷ����� ���ܰ� �߻��ϴ� ��츦 ����
  - ExceptionHandler ������̼��� �̿��� � ���ܰ� �߻��߳Ŀ� ���� �ش� �޼ҵ���� ����
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
- webapp/common/�� ���� view�� ������ jsp�� �����
