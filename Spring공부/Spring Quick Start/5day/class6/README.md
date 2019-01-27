# �������� JPA ����
- ������Ʈ ---> Properties ---> Project Facets ---> JPA �׸� üũ
- Spring ORM ���̺귯���� ���̹�����Ʈ ���̺귯�� �߰� (pom.xml�� dependency)
```
		<!-- JPA, ���̹�����Ʈ -->
		<dependency>
			<groupId>org.hibernate</groupId>
			<artifactId>hibernate-entitymanager</artifactId>
			<version>5.1.0.Final</version>
		</dependency>
	    	<dependency>
	    		<groupId>org.springframework</groupId>
	    		<artifactId>spring-orm</artifactId>
	    		<version>${org.springframework-version}</version>
	    	</dependency>
```
- JPA �������� (src/main/java/META-INF/persistence.xml) �ۼ�
```
	<persistence-unit name="springboard">
		<class>com.springbook.biz.board.BoardVO</class>
		<properties>
			<!-- �ʼ� �Ӽ� -->
			<property name="hibernate.dialect" value="org.hibernate.dialect.H2Dialect"/>
			
			<!-- �ɼ� -->
			<property name="hibernate.show_sql" value="true" />
			<property name="hibernate.format_sql" value="true" />
			<property name="hibernate.use_sql_comments" value="false" />
			<property name="hibernate.id.new_generator_mappings" value="true" />
			<property name="hibernate.hbm2ddl.auto" value="create" />
		</properties>
	</persistence-unit>
```
- ��ƼƼ Ŭ���� �ۼ� (BoardVO.java)
```
@Entity
@Table(name="BOARD")
public class BoardVO {
	@Id
	@GeneratedValue
	private int seq;
	private String title;
	private String writer;
	private String content;
	@Temporal(TemporalType.DATE)
	private Date regDate;
	private int cnt;
	@Transient
	private String searchCondition;
	@Transient
	private String searchKeyword;
	@Transient
	private MultipartFile uploadFile;
	...
}
```
- ������ �������Ͽ� JPA���� Ŭ������ bean�� ��� (applicationContext.xml)
```
	 <!-- Spring�� JPA ���� ���� -->
	 <bean id="jpaVendorAdapter" class="org.springframework.orm.jpa.vendor.HibernateJpaVendorAdapter"></bean>
	 
	 <bean id="entityManagerFactory" class="org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean">
	 	<property name="dataSource" ref="dataSource"></property>
	 	<property name="jpaVendorAdapter" ref="jpaVendorAdapter"></property>
	 </bean>

	 <!-- Transaction ���� -->
	 <bean id="txManager" class="org.springframework.orm.jpa.JpaTransactionManager">
	 	<property name="entityManagerFactory" ref="entityManagerFactory"></property>
	 </bean>
	 
	 <tx:advice id="txAdvice" transaction-manager="txManager">
	advice ���� ...
	aop ���� ...
```
- DAO Ŭ���� ����
```
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

import org.springframework.stereotype.Repository;

import com.springbook.biz.board.BoardVO;

@Repository
public class BoardDAOJPA {
	@PersistenceContext
	private EntityManager em;


	public void deleteBoard(BoardVO vo) {
		System.out.println("===> JPA�� deleteBoard ��� ó��");
		em.remove(em.find(BoardVO.class, vo.getSeq()));
	}
	
	public BoardVO getBoard(BoardVO vo) {
		System.out.println("===> JPA�� getBoard ��� ó��");
		return (BoardVO)em.find(BoardVO.class, vo.getSeq());
	}
	
	public List<BoardVO> getBoardList(BoardVO vo){
		System.out.println("===> JPA�� getBoardList ��� ó��");
		return em.createQuery("from BoardVO b order by b.seq desc").getResultList();
	}
	...
}
```