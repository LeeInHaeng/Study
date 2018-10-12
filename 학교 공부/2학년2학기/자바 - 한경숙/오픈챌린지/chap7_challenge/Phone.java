package chap7_challenge;

public class Phone {
	private String name;
	private String addr;
	private String tel;
	
	public Phone(String name, String addr, String tel)
	{
		this.name = name;
		this.addr = addr;
		this.tel = tel;
	}
	
	public void show()
	{
		System.out.println(name+" "+addr+" "+tel);
	}
}
