package chap4_challenge;

import java.util.Scanner;

public class GameMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int player = 0;
		WordGameApp game = new WordGameApp();
		player = game.Start();
		Player[] p = new Player[player];
		
		Scanner scan = new Scanner(System.in);
		for(int i=0; i<player; i++)
		{
			System.out.print("참가자의 이름을 입력하세요 >> ");
			String s = scan.next();
			p[i] = new Player(s);
		}
		
		int curPlayer = 0;
		System.out.println("시작하는 단어는 아버지 입니다");
		while(true)
		{
			System.out.print(p[curPlayer].getName()+ " >> ");
			String word = scan.next();
			boolean suc = p[curPlayer].sayWord(word);
			if(suc==false)
			{
				System.out.println(p[curPlayer].getName() + "이 졌습니다.");
				break;
			}
			else
			{
				curPlayer++;
				if(curPlayer == player)
					curPlayer = 0;
				p[curPlayer].SetWord(word);
				
			}
		}

	}

}
