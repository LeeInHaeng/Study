package com.demo.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;

import com.demo.interceptor.BoardInterceptor;

@Configuration
public class WebMvcConfig extends WebMvcConfigurerAdapter {
	
	  @Override
	  public void addInterceptors(InterceptorRegistry registry) {

		  registry.addInterceptor(new BoardInterceptor())
		  	.addPathPatterns("/board/*");
	  }
}
