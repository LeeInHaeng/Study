package chap3_challenge;

import java.util.Random;
import java.util.Scanner;

public class UpDownGame {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		int i = 1;
		int startNum = 0;
		int endNum = 0;
		GAME : while(true)
		{
			Random r = new Random();
			int res = r.nextInt(100);
			System.out.println("수를 결정 하였습니다. 맞추어 보세요 / 답 : " + res);
			System.out.println("0-99");
			
			while(true)
			{
				System.out.print(i + " >> ");
				int num = scan.nextInt();
				if(res==num)
				{
					System.out.println("맞았습니다.");
					System.out.println("다시 하시겠습니까?(y/n) >> ");
					String s = scan.next();
					if(s.equals("y"))
					{
						startNum = 0;
						endNum = 0;
						i = 1;
						break;
					}
					else
					{
						break GAME;
					}
				}
				else if(res > num)
				{
					startNum = num;
					System.out.println("더 높게");
					System.out.println(startNum + " - " + endNum);
					i++;
				}
				else
				{
					endNum = num;
					System.out.println("더 낮게");
					System.out.println(startNum + " - " + endNum);
					i++;
				}
			}

		}

		
	}

}
