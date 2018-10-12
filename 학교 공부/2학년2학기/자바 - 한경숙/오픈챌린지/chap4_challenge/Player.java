package chap4_challenge;

public class Player {
	private String name;
	private String word;
	
	public Player(String name)
	{
		this.name = name;
		word = "¾Æ¹öÁö";
	}
	
	public String getName()
	{
		return name;
	}
	
	public boolean sayWord(String answer)
	{
		int lastIndex = word.length()-1;
		char lastChar = word.charAt(lastIndex);
		if(answer.charAt(0) == lastChar)
			return true;
		else
			return false;
	}
	
	public void SetWord(String word)
	{
		this.word = word;
	}
}
