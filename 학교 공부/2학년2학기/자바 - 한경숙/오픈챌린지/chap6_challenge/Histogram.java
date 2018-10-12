package chap6_challenge;

import java.io.IOException;
import java.io.InputStreamReader;

public class Histogram {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("문장 입력을 시작합니다");
		int ch;
		int[] histo = new int[26];
		InputStreamReader rd = new InputStreamReader(System.in);
		
		while(true)
		{
			try {
				ch = rd.read();
				if(ch==-1)
					break;
				for(int i=0; i<26; i++)
				{
					if((ch == i+65) || (ch == i+97))
						histo[i]++;
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		System.out.println();
		System.out.println("히스토그램을 그립니다");
		for(int i=0; i<26; i++)
		{
			System.out.print((char)(i+97) + " ");
			for(int j=0; j<histo[i]; j++)
				System.out.print("-");
			System.out.println();
		}
	}

}
