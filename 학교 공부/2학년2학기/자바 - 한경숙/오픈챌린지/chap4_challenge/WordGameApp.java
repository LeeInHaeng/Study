package chap4_challenge;

import java.util.Scanner;

public class WordGameApp {
	public WordGameApp()
	{
		System.out.println("끝말잇기 게임을 시작합니다!");
	}
	
	public int Start()
	{
		Scanner scan = new Scanner(System.in);
		System.out.print("게임에 참가하는 인원은 몇명입니까 >> ");
		int num = scan.nextInt();
		return num;
	}
}
