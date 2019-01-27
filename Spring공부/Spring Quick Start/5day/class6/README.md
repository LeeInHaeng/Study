# 스프링과 JPA 연동
- 프로젝트 ---> Properties ---> Project Facets ---> JPA 항목 체크
- Spring ORM 라이브러리와 하이버네이트 라이브러리 추가 (pom.xml에 dependency)
```
		<!-- JPA, 하이버네이트 -->
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
- JPA 설정파일 (src/main/java/META-INF/persistence.xml) 작성
```
	<persistence-unit name="springboard">
		<class>com.springbook.biz.board.BoardVO</class>
		<properties>
			<!-- 필수 속성 -->
			<property name="hibernate.dialect" value="org.hibernate.dialect.H2Dialect"/>
			
			<!-- 옵션 -->
			<property name="hibernate.show_sql" value="true" />
			<property name="hibernate.format_sql" value="true" />
			<property name="hibernate.use_sql_comments" value="false" />
			<property name="hibernate.id.new_generator_mappings" value="true" />
			<property name="hibernate.hbm2ddl.auto" value="create" />
		</properties>
	</persistence-unit>
```
- 엔티티 클래스 작성 (BoardVO.java)
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
- 스프링 설정파일에 JPA관련 클래스를 bean에 등록 (applicationContext.xml)
```
	 <!-- Spring과 JPA 연동 설정 -->
	 <bean id="jpaVendorAdapter" class="org.springframework.orm.jpa.vendor.HibernateJpaVendorAdapter"></bean>
	 
	 <bean id="entityManagerFactory" class="org.springframework.orm.jpa.LocalContainerEntityManagerFactoryBean">
	 	<property name="dataSource" ref="dataSource"></property>
	 	<property name="jpaVendorAdapter" ref="jpaVendorAdapter"></property>
	 </bean>

	 <!-- Transaction 설정 -->
	 <bean id="txManager" class="org.springframework.orm.jpa.JpaTransactionManager">
	 	<property name="entityManagerFactory" ref="entityManagerFactory"></property>
	 </bean>
	 
	 <tx:advice id="txAdvice" transaction-manager="txManager">
	advice 설정 ...
	aop 설정 ...
```
- DAO 클래스 구현
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
		System.out.println("===> JPA로 deleteBoard 기능 처리");
		em.remove(em.find(BoardVO.class, vo.getSeq()));
	}
	
	public BoardVO getBoard(BoardVO vo) {
		System.out.println("===> JPA로 getBoard 기능 처리");
		return (BoardVO)em.find(BoardVO.class, vo.getSeq());
	}
	
	public List<BoardVO> getBoardList(BoardVO vo){
		System.out.println("===> JPA로 getBoardList 기능 처리");
		return em.createQuery("from BoardVO b order by b.seq desc").getResultList();
	}
	...
}
```