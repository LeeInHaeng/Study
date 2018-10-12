package chap7_challenge;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;

public class PhoneBook {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashMap<String,Phone> dic = new HashMap<String,Phone>();
		
		System.out.println("---------------------------------");
		System.out.println("전화번호 관리 프로그램을 시작합니다. 파일로 저장 안함");
		System.out.println("---------------------------------");
		
		Scanner scan = new Scanner(System.in);
		int sel;
		String name, addr, tel;
		
		Outter : while(true)
		{
			System.out.print("삽입:0, 삭제:1, 찾기:2, 전체보기:3, 종료:4 >> ");
			sel = scan.nextInt();
			switch(sel)
			{
			case 0:
				System.out.print("이름 >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
					System.out.println("중복된 이름이 있습니다!");
				else
				{
					System.out.print("주소 >> ");
					addr = scan.nextLine();
					System.out.print("전화번호 >> ");
					tel = scan.next();
					dic.put(name, new Phone(name,addr,tel));
				}

				break;
			case 1:
				System.out.print("이름 >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
				{
					dic.remove(name);
					System.out.println(name+"은 삭제되었습니다.");
				}
				else
					System.out.println(name+"는 등록되지 않은 사람입니다.");
				break;
			case 2:
				System.out.print("이름 >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
				{
					dic.get(name).show();
				}
				else
					System.out.println(name+"는 등록되지 않은 사람입니다.");
				break;
			case 3:
				Set<String> keys = dic.keySet();
				Iterator<String> it = keys.iterator();
				while(it.hasNext())
				{
					String PhoneKey = it.next();
					Phone tmp = dic.get(PhoneKey);
					tmp.show();
				}
				
				break;
			case 4:
				break Outter;
			}
			
		}
	}

}
