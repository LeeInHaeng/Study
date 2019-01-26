# JPA (Java Persistence API) �� ����
- ORM(Object-Relation Mapping)�� DB ������ �ʿ��� SQL�� �ڵ����� �����ϰ�, ������ SQL�� DBMS�� ����� �� �ڵ����� ����ȴ�.
- ORM �����ӿ�ũ�� Hibernate, TopLink, Cocobase ���� �����ߴ�.
- �̷��� ���� �����ӿ�ũ�鿡 ���� ǥ��ȭ �۾��� �ʿ��߰�, ORM ����ü���� ���� �������̽��� �����ϴ� ���� JPA��.
![123](https://user-images.githubusercontent.com/20277647/51786929-84599400-21ae-11e9-80c5-c4abb5edf379.png)

# ������Ʈ���� JPA ���
- ������Ʈ ��Ŭ�� ---> Properties ---> Project Facets ---> Convert to faceted form ---> JPA üũ
- JPA���� Runtimes ���� jdk üũ, Further configuration available Ŭ�� ---> JPA Implementation �׸񿡼� Type�� Disable Library Configuration���� ����
- JPA ���̺귯���� �߰��ϱ� ���� pom.xml���� dependency �߰�, ����� �����ͺ��̽� dependency �߰�
```
  	<!-- JPA, ���̹�����Ʈ -->
  	<dependency>
  		<groupId>org.hibernate</groupId>
  		<artifactId>hibernate-entitymanager</artifactId>
  		<version>5.1.0.Final</version>
  	</dependency>

  	<!-- H2 �����ͺ��̽� -->
  	<dependency>
  		<groupId>com.h2database</groupId>
  		<artifactId>h2</artifactId>
  		<version>1.4.197</version>
  	</dependency>
```
- ��ƼƼ Ŭ���� ���� (VO Ŭ������ ���)
  - ��Ű������ ��Ŭ�� ---> New ---> JPA Entity ---> Class name �Է� �� Finish
  - Entity ������̼� : ��ƼƼ Ŭ������ �ǹ��ϸ� ���̺�� ���εȴ�.
  - Table ������̼� : ��ƼƼ�� ���õ� ���̺��� ����, name �Ӽ��� ���� �� Ŭ���� �̸��� ���̺� �̸��� ���εȴ�.
  - Id ������̼� : �ʼ� ������̼�����, Ư�� ������ ���̺��� �⺻ Ű�� ����
  - GeneratedValue ������̼� : Id������̼��� ����� �ʵ忡 �⺻ Ű�� �ڵ����� �����Ͽ� �Ҵ��� �� ���
  - Temporal ������̼� : ��¥ Ÿ���� ������ �����Ͽ� ��¥ Ÿ���� ������ �� ���
```
@Entity
@Table(name="BOARD")
public class Board implements Serializable {
	@Id
	@GeneratedValue
	private int seq;
	private String title;
	private String writer;
	private String content;
	@Temporal(TemporalType.DATE)
	private Date regDate = new Date();
	private int cnt;
	private static final long serialVersionUID = 1L;

	// getter and setter 
	...
}
```
- JPA �������� properties ���� (src/main/java/META-INF/persistence.xml)
  - ���� Ŭ�������� �ڼ��� ����
- ������ JPA�� ����ϴ� Ŭ���̾�Ʈ ���α׷�(Ŭ����) �ۼ�
