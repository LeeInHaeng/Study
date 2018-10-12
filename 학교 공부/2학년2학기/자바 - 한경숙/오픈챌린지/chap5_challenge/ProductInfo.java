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
			System.out.print("상품추가(1), 모든 상품 조회(2), 끝내기(3) >> ");
			int sel = scan.nextInt();
			switch(sel)
			{
			case 1:
				System.out.print("상품 종류 책(1), 음악CD(2), 회화책(3) >> ");
				int sel2 = scan.nextInt();
				scan.nextLine();
				
				switch(sel2)
				{
				case 1:
					Book b = new Book();
					System.out.print("상품 설명 >> ");
					b.comment = scan.nextLine();
					System.out.print("생산자 >> ");
					b.creator = scan.nextLine();
					System.out.print("가격 >> ");
					b.price = scan.nextInt();
					scan.nextLine();
					System.out.print("책제목 >> ");
					b.bookTitle = scan.nextLine();
					System.out.print("저자 >> ");
					b.author = scan.nextLine();
					list.add(b);
					cnt++;
					break;
				case 2:
					CompactDisc cd = new CompactDisc();
					System.out.print("상품 설명 >> ");
					cd.comment = scan.nextLine();
					System.out.print("생산자 >> ");
					cd.creator = scan.nextLine();
					System.out.print("가격 >> ");
					cd.price = scan.nextInt();
					scan.nextLine();
					System.out.print("앨범 제목 >> ");
					cd.albumTitle = scan.nextLine();
					System.out.print("가수 >> ");
					cd.singer = scan.nextLine();
					list.add(cd);
					cnt++;
					break;
				case 3:
					ConversationBook cb = new ConversationBook();
					System.out.print("상품 설명 >> ");
					cb.comment = scan.nextLine();
					System.out.print("생산자 >> ");
					cb.creator = scan.nextLine();
					System.out.print("가격 >> ");
					cb.price = scan.nextInt();
					scan.nextLine();
					System.out.print("책제목 >> ");
					cb.bookTitle = scan.nextLine();
					System.out.print("저자 >> ");
					cb.author = scan.nextLine();
					System.out.print("책 언어 >> ");
					cb.language = scan.nextLine();
					list.add(cb);
					cnt++;
					break;
				}
				
				break;
			case 2:
				for(int j=0; j<cnt; j++)
				{
					System.out.println("상품 ID >> " + j+1);
					list.get(j).show();
				}
				break;
			case 3:
				break Outter;
			default:
				System.out.println("잘못 입력 하셨습니다!");
				break;
			}
		}

	}

}
