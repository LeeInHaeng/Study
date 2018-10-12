package chap2_challenge;

import java.util.Scanner;

public class GBBGame {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		System.out.println("가위 바위 보 게임입니다. 가위, 바위, 보 중에서 입력하세요");
		System.out.print("철수 >> ");
		String s1 = scan.next();
		System.out.print("영희 >> ");
		String s2 = scan.next();
		
		if(s1.equals(s2))
			System.out.println("비겼습니다");
		
		if(s1.equals("가위") && s2.equals("바위"))
			System.out.println("영희가 이겼습니다");
		else if(s1.equals("가위") && s2.equals("보"))
			System.out.println("철수가 이겼습니다");
		// 생략

	}

}
