# ������ ����
- Dependency Lookup : �����̳ʰ� ���ø����̼� ��뿡 �ʿ��� ��ü�� �����ϰ� Ŭ���̾�Ʈ�� �����̳ʰ� ������ ��ü�� �˻��Ͽ� ����ϴ� ���
- Dependency Injection : ��ü ������ �������踦 ������ ���� ���Ͽ� ��ϵ� ������ �������� �����̳ʰ� �ڵ����� ó�� ---> ��κ��� ��� �� ����� ���

# Dependency Injection �� ������ ������ �̿�
- �Ű������� �ִ� �����ڸ� ���� (SamsungTV.java)
- XML ���� ���Ͽ��� constructor-arg ������Ʈ�� �߰��Ͽ� ������ �Ű������� �Ѱ���
  - ref �Ӽ����� bean ����
  - ���� 2�� �̻��� �Ű������� �ʿ��ϸ� constructor-arg�� �Ű����� ������ŭ ���� (�� ������ ���� value)

# Dependency Injection �� Setter ������ �̿�
- set�޼ҵ� ���� (SamsungTV.java) ex) public void setSpeaker(Speaker speaker)
- XML ���� ���Ͽ��� property ������Ʈ�� �߰��Ͽ� ref, value �Ӽ� ���� ����
  - name �Ӽ��� ��� .java���� set�� ���� �ҹ��ڷ� ���� (ex1 : setSpeaker() ---> name="speaker" , ex2 : setBoardDAO() ---> name="boardDAO")

# Setter ������ ���� �� p ���ӽ����̽� ����ϴ� ���
- XML ���� ���Ͽ��� xmlns:p="http://www.springframework.org/schema/p" ����
- p:������-ref="������ ��ü�� �̸��̳� ���̵�"
- p:������="������ ��"

# List Ÿ�� ����
- java���� import java.util.List;
- java���� List ��� (ex : private List<String> addressList;)
- XML ���� ���Ͽ��� list ������Ʈ ���, �� ������ value ������Ʈ�� ����
```
<list>
	<value>����� ������ ���ﵿ</value>
	<value>����� ������ ��絿</value>
</list>
```

# Set Ÿ�� ����
- java���� import java.util.Set;
- java���� Set ��� (ex : private Set<String> addressList;)
- XML ���� ���Ͽ��� set ������Ʈ ���, �� ������ value ������Ʈ�� ����
```
<set value-type="java.lang.String">
	<value>����� ������ ���ﵿ</value>
	<value>����� ������ ������</value>
	<value>����� ������ ������</value>
</set>
```

# Map Ÿ�� ����
- java���� import java.util.Map;
- java���� Set ��� (ex : private Map<String, String> addressList;)
- XML ���� ���Ͽ��� map ������Ʈ ���, �� Ű �� entry ������Ʈ ���, Ű ���� key ������Ʈ ���, �� ������ value ������Ʈ�� ����
```
<map>
	<entry>
		<key><value>��浿</value></key>
		<value>����� ������ ���ﵿ</value>
	</entry>
	<entry>
		<key><value>������</value></key>
		<value>����� ������ ȭ�</value>
	</entry>
</map>
```

# Properties Ÿ�� ����
- java���� import java.util.Properties;
- java���� Properties ��� (ex : private Properties addressList;)
- XML ���� ���Ͽ��� props ������Ʈ ���, prop ������Ʈ�� Ű�� ���� �� ����
```
<props>
	<prop key="��浿">����� ������ ���ﵿ</prop>
	<prop key="������">����� ������ ȭ�</prop>
</props>
```