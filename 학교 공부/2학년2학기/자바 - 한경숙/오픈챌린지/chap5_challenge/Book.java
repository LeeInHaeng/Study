package chap5_challenge;

public class Book extends Product {
	public String ISBNNum;
	public String author;
	public String bookTitle;
	
	public void show()
	{
		super.show();
		System.out.println("ISBN ��ȣ : " + ISBNNum);
		System.out.println("���� : " + author);
		System.out.println("å���� : " + bookTitle);
	}
}
