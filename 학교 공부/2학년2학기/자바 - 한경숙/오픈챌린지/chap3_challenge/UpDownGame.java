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
			System.out.println("���� ���� �Ͽ����ϴ�. ���߾� ������ / �� : " + res);
			System.out.println("0-99");
			
			while(true)
			{
				System.out.print(i + " >> ");
				int num = scan.nextInt();
				if(res==num)
				{
					System.out.println("�¾ҽ��ϴ�.");
					System.out.println("�ٽ� �Ͻðڽ��ϱ�?(y/n) >> ");
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
					System.out.println("�� ����");
					System.out.println(startNum + " - " + endNum);
					i++;
				}
				else
				{
					endNum = num;
					System.out.println("�� ����");
					System.out.println(startNum + " - " + endNum);
					i++;
				}
			}

		}

		
	}

}
