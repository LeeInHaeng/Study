package chap5_challenge;

public class CompactDisc extends Product {
	public String albumTitle;
	public String singer;
	
	public void show()
	{
		super.show();
		System.out.println("앨범 제목 : " + albumTitle);
		System.out.println("가수 : " + singer);
	}
}
