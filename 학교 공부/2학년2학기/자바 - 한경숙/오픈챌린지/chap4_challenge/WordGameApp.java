package chap4_challenge;

import java.util.Scanner;

public class WordGameApp {
	public WordGameApp()
	{
		System.out.println("�����ձ� ������ �����մϴ�!");
	}
	
	public int Start()
	{
		Scanner scan = new Scanner(System.in);
		System.out.print("���ӿ� �����ϴ� �ο��� ����Դϱ� >> ");
		int num = scan.nextInt();
		return num;
	}
}
