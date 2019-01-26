package com.springbook.biz.common;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Service;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Aspect;

@Service
@Aspect
public class LogAdvice {
	/*
	@Pointcut("execution(* com.springbook.biz..*Impl.*(..))")
	public void allPointcut() {}
	
	// <aop:before> 엘리먼트 중 pointcut-ref에 해당함.
	@Before("allPointcut()")
	// <aop:before> 엘리먼트 중 method에 해당함.
	 */
	@Before("PointcutCommon.allPointcut()")
	public void printLog() {
		System.out.println("[공통 로그] 비즈니스 로직 수행 전 동작");
	}
	
	@Pointcut("execution(* com.springbook.biz..*Impl.get*(..))")
	public void getPointcut() {}
}
