# Eclipse ȯ�漳��
- Help ---> Eclipse Marketplace ---> Spring Tools 4 - for Spring Boot ��ġ (4.4.1) (������ �������� ��ġ)
- Eclipse ������ ����� Perspective���� Spring�� ����
- File ---> New ---> Spring Starter Project
- Name : boot01 / Group : org.zerock / Package : org.zerock / Packaging : War ---> Next
- Core���� Lombok ����, Web���� Web ���� ---> Finish
- src/main/java�� ������Ʈ �̸�+Application.java�� Spring Boot App���� ����
- ������ Controller�� ����� �׽�Ʈ �غ��� (localhost:8080/hello) ---> ��Ĺ default ��Ʈ ���� 8080
```
// SampleController.java
package org.zerock.controller;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;

@RestController
public class SampleController {

	@GetMapping("/hello")
	public String sayHello() {
		return "Hello World";
	}
}

```

# ������ ��Ʈ�� ����
- ������ ������ ���� ��Ŀ��� �����ߴ� �����̳� ���� �浹 ���� ������ ���ִ� ��ſ� ������ ���� ���� ȯ��� �׽�Ʈ ȯ�� ���� �� ���� ����
- �ڵ�ȭ�� ���̺귯�� ����
- Spring Boot Auto Configure
- ������ ���̺귯�� �ڵ� ������ XML ���� ȯ�� ����
- �׽�Ʈ ȯ��� ���� Tomcat
