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
		System.out.println("��ȭ��ȣ ���� ���α׷��� �����մϴ�. ���Ϸ� ���� ����");
		System.out.println("---------------------------------");
		
		Scanner scan = new Scanner(System.in);
		int sel;
		String name, addr, tel;
		
		Outter : while(true)
		{
			System.out.print("����:0, ����:1, ã��:2, ��ü����:3, ����:4 >> ");
			sel = scan.nextInt();
			switch(sel)
			{
			case 0:
				System.out.print("�̸� >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
					System.out.println("�ߺ��� �̸��� �ֽ��ϴ�!");
				else
				{
					System.out.print("�ּ� >> ");
					addr = scan.nextLine();
					System.out.print("��ȭ��ȣ >> ");
					tel = scan.next();
					dic.put(name, new Phone(name,addr,tel));
				}

				break;
			case 1:
				System.out.print("�̸� >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
				{
					dic.remove(name);
					System.out.println(name+"�� �����Ǿ����ϴ�.");
				}
				else
					System.out.println(name+"�� ��ϵ��� ���� ����Դϴ�.");
				break;
			case 2:
				System.out.print("�̸� >> ");
				name = scan.next();
				scan.nextLine();
				
				if(dic.containsKey(name))
				{
					dic.get(name).show();
				}
				else
					System.out.println(name+"�� ��ϵ��� ���� ����Դϴ�.");
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
