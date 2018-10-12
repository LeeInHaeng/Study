package chap5_challenge;

public class ConversationBook extends Book {

	public String language;
	
	public void show()
	{
		super.show();
		System.out.println("¾ð¾î : " + language);
	}
}
