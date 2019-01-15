# Context ���ӽ����̽�
- STS Namespaces �ǿ��� context ���� �� �߰�

- ������ ���� ���Ͽ� ����� ��ü���� <bean> �� ������� �ʰ� �ڵ����� �����ϱ� ���� <context:component-scan> ���
  - XML ���� ���Ͽ��� <context:component-scan base-package="��Ű����"></context:component-scan>

- .java ���Ͽ� Annotation ���� : @ComponentScan("tv")
  - import org.springframework.stereotype.Component;

# ������̼�
- @Autowired : �ַ� ���� ���� �����Ͽ� �ش� Ÿ���� ��ü�� ã�Ƽ� �ڵ����� �Ҵ�
  - import org.springframework.beans.factory.annotation.Autowired;
```
@Autowired
private Speaker speaker;
```
  - ������ ���Կ� ����ߴ� Setter �޼ҵ峪 �����ڰ� �ʿ� ���� �ڵ����� ��ü ����
  - ��, �ش� ��ü�� �޸𸮿� �ö� �־�� �ϹǷ� SonySpeaker.java ���� @Component("sony") ����

- @Qualifier : Ư�� ��ü�� �̸��� �̿��Ͽ� ������ ������ �� ���
  - Autowired���� �޸𸮿� �ö�� ��ü�� 2�� �̻��� �� �浹�� �߻��ϹǷ� �ش� ������̼��� ���
  - import org.springframework.beans.factory.annotation.Qualifier;
```
@Autowired
@Qualifier("apple")
private Speaker speaker;
```

- @Resource : @Autowired�� @Qualifier�� ��ģ ������̼�, Spring ������̼��� �ƴ� �ڹ� ������ ������̼�
  - import javax.annotation.Resource;
```
@Resource(name="apple")
private Speaker speaker;
```

- ���� Speaker ��üó�� ����� �� �ִ� �κ��� xml���� <bean>���� ��� ��, Autowired ������̼Ǹ� ����ϴ� ����� ����. (Component ������̼��� ������ ��ü�� �ڵ����� �޸𸮿� �ö󰡴� ���� ���ش�.)
  - XML�� �����ϱ⿡�� <bean> ����� �������� ���� ���� ������ �δ㽺����.
  - ������̼Ǹ� ������ڴ� �ڹ� �ҽ��� �����ؾ� ���� ���踦 ������ �� �ִ�.
  - �� �� ���� ����� �����ؼ� ������ ���!
```
@Autowired
private Speaker speaker;

<bean class="polymorphism.SonySpeaker"></bean>
```