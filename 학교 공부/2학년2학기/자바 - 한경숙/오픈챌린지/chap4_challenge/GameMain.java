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
			System.out.print("�������� �̸��� �Է��ϼ��� >> ");
			String s = scan.next();
			p[i] = new Player(s);
		}
		
		int curPlayer = 0;
		System.out.println("�����ϴ� �ܾ�� �ƹ��� �Դϴ�");
		while(true)
		{
			System.out.print(p[curPlayer].getName()+ " >> ");
			String word = scan.next();
			boolean suc = p[curPlayer].sayWord(word);
			if(suc==false)
			{
				System.out.println(p[curPlayer].getName() + "�� �����ϴ�.");
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
