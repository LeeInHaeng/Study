package chap5_challenge;

public class Book extends Product {
	public String ISBNNum;
	public String author;
	public String bookTitle;
	
	public void show()
	{
		super.show();
		System.out.println("ISBN 번호 : " + ISBNNum);
		System.out.println("저자 : " + author);
		System.out.println("책제목 : " + bookTitle);
	}
}
