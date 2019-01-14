# ������ �����̳� �� ���� ����
- ������Ʈ�� src/main/resources�� Spring Bean Configuration File�� ����
  - ���� xml ���Ͽ� bean ������Ʈ �Է� (id�� class)

# ������ �����̳� ���� �� �׽�Ʈ
- 1. Spring �����̳ʸ� �����Ѵ�.
  - import org.springframework.context.support.AbstractApplicationContext;
  - import org.springframework.context.support.GenericXmlApplicationContext;
  - AbstractApplicationContext factory = new GenericXmlApplicationContext("������ ����.xml");

- 2. Spring �����̳ʷκ��� �ʿ��� ��ü�� ��û(Lookup) �Ѵ�.
  - TV tv = (TV)factory.getBean("tv");
  - getBean ���� ���ڴ� xml���� ���� ������ bean ������Ʈ�� id�� �ִ´�.
  - �ش� id�� ��Ī�Ǵ� class�� ���� �� �ִ�.

- 3. Spring �����̳ʸ� �����Ѵ�.
  - factory.close();

# ApplicationContext
- BeanFactory�� �����ϴ� bean ��ü ���� ��� + Ʈ����� ���� + �޽��� ����� �ٱ��� ó�� �� �پ��� ���
- �����̳ʰ� �����Ǵ� ������ bean ��ϵ� Ŭ�������� ��ü �����ϴ� ��� �ε� ������� ����
- �� ���ø����̼� ���� ���� ����
- GenericXmlApplicationContext : ���� �ý����̳� Ŭ���� ��ο� �ִ� XML ���� ������ �ε��Ͽ� �����ϴ� �����̳�
- XmlWebApplicationContext : �� ����� ������ ���ø����̼��� ������ �� ����ϴ� �����̳�

# ������ XML ����
- import ������Ʈ : ���� ������ �Ǿ� �ִ� �ٸ� xml ������ import �Ѵ�.
  - <import resource="myxml.xml"/>

- bean ������Ʈ : ������ ���� ���Ͽ� Ŭ������ ����ϱ� ���� ���
  - id�� ������ ���������� class�� �ʼ� �Ӽ� <bean id="~" class="~"></bean>
  - name �Ӽ� ���� id�� ���������� ��ü ������ ���� ������ �����ؾ� ������ Ư����ȣ ������ �����ϴ�.

# bean ������Ʈ �Ӽ�
- init-method �Ӽ� : ��ü ���� �� ������ ȣ�� �Ŀ� ������� �ʱ�ȭ �۾��� �ʿ��� ��� �ַ� ���
  - <bean id="tv" class="SamsungTV" init-method="initMethod"/>
  - SamsungTV.java���� public void initMethod() ����

- destroy-method �Ӽ� : ������ �����̳ʰ� ��ü�� �����ϱ� ������ ȣ��Ǵ� ������ �޼ҵ带 ������ �� �ִ�.
  - <bean id="tv" class="SamsungTV" destroy-method="destroyMethod"/>
  - SamsungTV.java���� public void destroyMethod() ����

- lazy-init �Ӽ� : ���� ������ �ʴ� bean�� ��� �޸𸮸� ���� �����Ͽ� �δ��� �� �� �ֱ� ������ bean�� ���Ǵ� ������ ��ü�� �����ϵ��� �ϴ� �Ӽ�
  - <bean ~~ lazy-init="true"/>

- scope �Ӽ� : �� ��ü���� Ư���� ���� ��� �ϳ��� ��ü�� �����ŵ� �Ǳ� ������ �ʿ��� �Ӽ�
  - <bean ~~ scope="singleton"/> ---> ��κ� �̱������� � �Ǵ� ���� �ٶ����ϴ�.
  - �Ź� ���ο� ��ü�� �����ϰ� �ʹٸ� scope="prototype"���� ����