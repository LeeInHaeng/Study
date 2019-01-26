# JPA ��������
- persistence-unit ������Ʈ : ��Ʈ ������Ʈ�� ���߿� DAO Ŭ���� ���� �� ����� name�� �����Ѵ�.
```
<persistence-unit name="JPAProject">
```
- class ������Ʈ : Entity Ŭ������ ����Ѵ�.
```
	<persistence-unit name="JPAProject">
		<class>com.springbook.biz.board.Board</class>
```
- �����ͺ��̽��� ������ �Ӽ��� ����Ѵ�. ���߿� Spring�� �����ÿ��� DataSource�� ����� ���� ������ �ش� �κ��� �����Ѵ�.
```
	<persistence-unit name="JPAProject">
		<class>com.springbook.biz.board.Board</class>
		<properties>
			<!-- �ʼ� �Ӽ� -->
			<property name="javax.persistence.jdbc.driver" value="org.h2.Driver"/>
			<property name="javax.persistence.jdbc.user" value="sa" />
			<property name="javax.persistence.jdbc.password" value="" />
			<property name="javax.persistence.jdbc.url" value="jdbc:h2:tcp://localhost/~/test" />
```
- Dialect Ŭ���� : �ش� DBMS�� ����ȭ�� SQL ������ ������ �ش�.
  - ���������� H2 �����ͺ��̽��� ����ϹǷ�, �ش� �����ͺ��̽��� Dialect�� �����Ѵ�.
  - DBMS ���� �� Dialect Ŭ������ �����ϸ� SQL�� �ڵ����� ����Ǿ� �����ǹǷ� ���������� ũ�� ���ȴ�.
```
			<property name="hibernate.dialect" value="org.hibernate.dialect.H2Dialect" />
```
- ���̹�����Ʈ ���� �Ӽ� ����
  - hibernate.show_sql : ������ SQL�� �ֿܼ� ����Ѵ�.
  - hibernate.format_sql : SQL�� ����� ��, ������ �������� ���� ���� ����Ѵ�.
  - hibernate.use_sql_comments : SQL�� ���Ե� �ּ��� ���� ����Ѵ�.
  - hibernate.id.new_generator_mappings : ���ο� Ű ���� ������ ����Ѵ�.
  - hibernate.hbm2ddl.auto : ���̺� �����̳� ����, ���� ���� DDL ������ �ڵ����� ó�������� �����Ѵ�.
  - hibernate.hbm2ddl.auto ������ create, create-drop, update �Ӽ��� �ִ�.
  - create : ���ø����̼��� ������ ��, ���� ���̺��� �����ϰ� ���ο� ���̺��� �����Ѵ�. (DROP --> CREATE)
  - create-drop : create�� ������ ���ø����̼��� ����Ǳ� ������ ������ ���̺��� �����Ѵ�. (DROP --> CREATE --> DROP)
  - update : ������ ��� ���� ���̺��� ������ ���̺��� ���������� �ʰ� �����Ѵ�. ���� ��ƼƼ Ŭ������ ���� ������ ����Ǹ� ����� ���븸 �ݿ��Ѵ�. (ALTER)
```
			<!-- �ɼ� -->
			<property name="hibernate.show_sql" value="true" />
			<property name="hibernate.format_sql" value="true" />
			<property name="hibernate.use_sql_comments" value="false" />
			<property name="hibernate.id.new_generator_mappings" value="true" />
			<property name="hibernate.hbm2ddl.auto" value="create" />
```

# EntityManager ��ü�� �����ϴ� CRUD ����� �޼ҵ��
- persist(Object entity) : ��ƼƼ�� ����ȭ�Ѵ�. (INSERT)
- merge(Object entity) : �ؿ��� ������ ��ƼƼ�� ����ȭ�Ѵ�. (UPDATE)
- remove(Object entity) : ���� ������ ��ƼƼ�� �����Ѵ�. (DELETE)
- find(Class<T> entityClass, Object primaryKey) : �ϳ��� ��ƼƼ�� �˻��Ѵ�. (SELECT ONE)
- createQuery(String qlString, class<T> resultClass) : JPQL�� �ش��ϴ� ��ƼƼ ����� �˻��Ѵ�. (SELECT LIST)