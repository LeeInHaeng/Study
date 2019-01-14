package com.springboo.ioc.injection;

import java.util.List;
import java.util.Set;
import java.util.Map;
import java.util.Properties;

import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.context.support.GenericXmlApplicationContext;
import com.springboo.ioc.injection.CollectionBean;

public class CollectionBeanClient {

	public static void main(String[] args) {
		AbstractApplicationContext factory = new GenericXmlApplicationContext("applicationContext.xml");
		
		CollectionBean bean = (CollectionBean)factory.getBean("collectionBean");
		//List<String> addressList = bean.getAddressList();
		//Set<String> addressList = bean.getAddressList();
		//Map<String, String> addressList = bean.getAddressList();
		Properties addressList = bean.getAddressList();
		
		/*
		for(String address : addressList) {
			System.out.println(address.toString());
		}
		*/
		/*
		for(String key : addressList.keySet()) {
			System.out.println(key);
			System.out.println(addressList.get(key));
		}
		*/
		for(String key : addressList.stringPropertyNames()) {
			System.out.println(key);
			System.out.println(addressList.getProperty(key));
		}
		
		factory.close();
	}

}
