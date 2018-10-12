package chap5_challenge;

public class Product {
	public String comment;
	public String creator;
	public int price;
	
	public void show()
	{
		System.out.println("상품 설명 >> " + comment);
		System.out.println("생산자 >> " +creator);
		System.out.println("가격 >> " + price);
	}
}
