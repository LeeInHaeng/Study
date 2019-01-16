# AOP ��� ����
- Joinpoint : Ŭ���̾�Ʈ�� ȣ���ϴ� ��� ����Ͻ� �޼ҵ�, '����Ʈ�� ���' �Ǵ� '����Ʈ�� �ĺ�'��� �Ѵ�.

- Pointcut : ���͸��� ��������Ʈ, �� ������ ����Ͻ� �޼ҵ� �߿��� �츮�� ���ϴ� Ư�� �޼ҵ忡���� Ⱦ�� ���ɿ� �ش��ϴ� ���� ����� �����Ű�� ���� �ʿ�
  - expression �Ӽ��� �̿��Ͽ� ���͸�
```
<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
<aop:pointcut expression="execution(* com.springbook.biz..*Impl.get*(..))" id="getPointcut"/>
```
  - * : ���� Ÿ��
  - com.springbook.biz.. : ��Ű�� ���
  - *Impl : Ŭ���� ��
  - *(..) : �޼ҵ�� �� �Ű� ����

  - �� com.springbook.biz ��Ű���� �����ϴ� Ŭ���� �߿��� �̸��� Impl�� ������ Ŭ������ ����
  - �ش� Ŭ�������� *(..)�� ��� �޼ҵ带 ����Ʈ ������ �����ϰ�, get*(..)�� get���� �����ϴ� �޼ҵ常 ����Ʈ������ ����
  - ���������� Advice�� �̿��Ͽ� pointcut�� ���� �� �޼ҵ� ����

- Advice : Ⱦ�� ���ɿ� �ش��ϴ� ���� ����� �ڵ带 �ǹ��ϸ�, ������ Ŭ������ �޼ҵ�� �ۼ�, ���� �������� ����
  - <aop:before>, <aop:after>, <aop:after-returnning>, <aop:throwing>, <aop:round>�� ���� ���� ����
```
<aop:before method="printLog" pointcut-ref="allPointcut"/>
```

- Aspect �Ǵ� Advisor : � ����Ʈ�� �޼ҵ忡 ���ؼ� � �����̽� �޼ҵ带 �������� ����
```
<bean id="log" class="com.springbook.biz.common.LogAdvice"></bean>
<aop:config>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.*(..))" id="allPointcut"/>
	<aop:pointcut expression="execution(* com.springbook.biz..*Impl.get*(..))" id="getPointcut"/>
	<aop:aspect ref="log"> ----> Aspect �Ǵ� Advisor !!�߿�!!
		<aop:before method="printLog" pointcut-ref="allPointcut"/>
	</aop:aspect>
</aop:config>
```
  - Advisor�� ��쿡�� ����Ʈ���� ���̵� �𸣰ų�, �޼ҵ� �̸��� Ȯ���� �� ���� ��� ��� (Ʈ����� ó��)
```
// method ���� �𸣱� ������ advice-ref�� �̿��Ͽ� advice�� ����
<aop:advisor advice-ref="txAdvice" pointcut-ref="allPointcut"/>
```

# ����Ʈ�� ǥ����
- ���� Ÿ��
  - * : ��� ����Ÿ�� ���
  - void : ����Ÿ���� void�� �޼ҵ� ����
  - !void : ����Ÿ���� void�� �ƴ� �޼ҵ� ����

- ��Ű�� ���
  - com.springbook.biz : ��Ȯ�ϰ� com.springbook.biz ��Ű���� ����
  - com.springbook.biz.. : com.springbook.biz ��Ű���� �����ϴ� ��� ��Ű�� ����
  - com.springbook..impl : com.springbook ��Ű���� �����ϸ鼭 ������ ��Ű�� �̸��� impl�� ������ ��Ű�� ����

- Ŭ���� ��
  - BoardServiceImpl : ��Ȯ�ϰ� BoardServiceImpl Ŭ������ ����
  - *Impl : Ŭ���� �̸��� Impl�� ������ Ŭ������ ����
  - BoardService+ : BoardService Ŭ�����κ��� �Ļ��� ��� �ڽ� Ŭ���� ����

- �޼ҵ� ��
  - *(..) : ���� �⺻ �������� ��� �޼ҵ� ����
  - get*(..) : �޼ҵ� �̸��� get���� �����ϴ� ��� �޼ҵ� ����

- �Ű����� ����
  - (..) : ���� �⺻ �������μ� �Ű������� ������ Ÿ�Կ� ������ ������ �ǹ�
  - (*) : �ݵ�� 1���� �Ű������� ������ �޼ҵ常 ����
  - (com.springbook.user.UserVO) : �Ű������� UserVO�� ������ �޼ҵ常 ����, �̶� Ŭ������ ��Ű�� ��ΰ� �ݵ�� ���ԵǾ�� �Ѵ�.
  - (!com.springbook.user.UserVO) : �Ű������� UserVO�� ������ �ʴ� �޼ҵ常 ����
  - (Integer, ..) : �� �� �̻��� �Ű������� ������, ù ��° �Ű������� Ÿ���� Integer�� �޼ҵ常 ����
  - (Integer, *) : �ݵ�� �� ���� �Ű������� ������, ù ��° �Ű������� Ÿ���� Integer�� �޼ҵ常 ����