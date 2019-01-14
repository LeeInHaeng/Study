package com.springboo.ioc.injection;

import java.util.List;
import java.util.Set;
import java.util.Map;
import java.util.Properties;

public class CollectionBean {
	//private List<String> addressList;
	//private Set<String> addressList;
	//private Map<String, String> addressList;
	private Properties addressList;
	
	/*
	public void setAddressList(List<String> addressList) {
		this.addressList = addressList;
	}
	*/
	
	/*
	public void setAddressList(Set<String> addressList) {
		this.addressList = addressList;
	}
	*/
	
	/*
	public void setAddressList(Map<String, String> addressList) {
		this.addressList = addressList;
	}
	*/
	
	public void setAddressList(Properties addressList) {
		this.addressList = addressList;
	}
	
	/*
	public List<String> getAddressList(){
		return addressList;
	}
	*/
	
	/*
	public Set<String> getAddressList(){
		return addressList;
	}
	*/
	/*
	public Map<String, String> getAddressList(){
		return addressList;
	}
	*/
	public Properties getAddressList(){
		return addressList;
	}
}
