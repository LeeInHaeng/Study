package chap5_challenge;

public class CompactDisc extends Product {
	public String albumTitle;
	public String singer;
	
	public void show()
	{
		super.show();
		System.out.println("�ٹ� ���� : " + albumTitle);
		System.out.println("���� : " + singer);
	}
}
