package chap5_challenge;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class ProductInfo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<Product> list = new ArrayList<Product>();
		Scanner scan = new Scanner(System.in);
		int cnt = 0;
		
		Outter : while(true)
		{
			System.out.print("��ǰ�߰�(1), ��� ��ǰ ��ȸ(2), ������(3) >> ");
			int sel = scan.nextInt();
			switch(sel)
			{
			case 1:
				System.out.print("��ǰ ���� å(1), ����CD(2), ȸȭå(3) >> ");
				int sel2 = scan.nextInt();
				scan.nextLine();
				
				switch(sel2)
				{
				case 1:
					Book b = new Book();
					System.out.print("��ǰ ���� >> ");
					b.comment = scan.nextLine();
					System.out.print("������ >> ");
					b.creator = scan.nextLine();
					System.out.print("���� >> ");
					b.price = scan.nextInt();
					scan.nextLine();
					System.out.print("å���� >> ");
					b.bookTitle = scan.nextLine();
					System.out.print("���� >> ");
					b.author = scan.nextLine();
					list.add(b);
					cnt++;
					break;
				case 2:
					CompactDisc cd = new CompactDisc();
					System.out.print("��ǰ ���� >> ");
					cd.comment = scan.nextLine();
					System.out.print("������ >> ");
					cd.creator = scan.nextLine();
					System.out.print("���� >> ");
					cd.price = scan.nextInt();
					scan.nextLine();
					System.out.print("�ٹ� ���� >> ");
					cd.albumTitle = scan.nextLine();
					System.out.print("���� >> ");
					cd.singer = scan.nextLine();
					list.add(cd);
					cnt++;
					break;
				case 3:
					ConversationBook cb = new ConversationBook();
					System.out.print("��ǰ ���� >> ");
					cb.comment = scan.nextLine();
					System.out.print("������ >> ");
					cb.creator = scan.nextLine();
					System.out.print("���� >> ");
					cb.price = scan.nextInt();
					scan.nextLine();
					System.out.print("å���� >> ");
					cb.bookTitle = scan.nextLine();
					System.out.print("���� >> ");
					cb.author = scan.nextLine();
					System.out.print("å ��� >> ");
					cb.language = scan.nextLine();
					list.add(cb);
					cnt++;
					break;
				}
				
				break;
			case 2:
				for(int j=0; j<cnt; j++)
				{
					System.out.println("��ǰ ID >> " + j+1);
					list.get(j).show();
				}
				break;
			case 3:
				break Outter;
			default:
				System.out.println("�߸� �Է� �ϼ̽��ϴ�!");
				break;
			}
		}

	}

}
