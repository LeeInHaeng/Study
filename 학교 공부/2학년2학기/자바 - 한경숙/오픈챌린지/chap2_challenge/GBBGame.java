package chap2_challenge;

import java.util.Scanner;

public class GBBGame {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		System.out.println("���� ���� �� �����Դϴ�. ����, ����, �� �߿��� �Է��ϼ���");
		System.out.print("ö�� >> ");
		String s1 = scan.next();
		System.out.print("���� >> ");
		String s2 = scan.next();
		
		if(s1.equals(s2))
			System.out.println("�����ϴ�");
		
		if(s1.equals("����") && s2.equals("����"))
			System.out.println("���� �̰���ϴ�");
		else if(s1.equals("����") && s2.equals("��"))
			System.out.println("ö���� �̰���ϴ�");
		// ����

	}

}
