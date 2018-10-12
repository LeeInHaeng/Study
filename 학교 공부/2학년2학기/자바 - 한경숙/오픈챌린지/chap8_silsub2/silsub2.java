package chap8_silsub2;
import java.io.*;
import java.util.*;

public class silsub2 {

	public static void clear(char[] c){
		for(int i=0; i<c.length; i++)
			c[i] = '\0';
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileReader fr = null;
		BufferedReader br = null;
		ArrayList<String> al = new ArrayList<String>();
		LinkedList<String> stack = new LinkedList<String>();
		int c;
		char[] tmp = new char[100];
		int i =0;
		
		try{
			fr = new FileReader("c:\\Windows\\system.ini");
			br = new BufferedReader(fr,100);
			while((c = br.read()) != -1){
				if(c=='\r')
				{
					al.add(String.valueOf(tmp));
					clear(tmp);
					i = 0;
				}
				else
				{
					tmp[i] = (char)c;
					i++;
				}
				
			}
			
			System.out.println("------입력순------");
			for(int j=0; j<al.size(); j++)
				System.out.print(al.get(j));
			
			System.out.println();
			System.out.println();
			
			System.out.println("-------역순--------");
			for(int j=0; j<al.size(); j++){
				stack.push(al.get(j));
			}
			for(int j=0; j<al.size(); j++)
				System.out.print(stack.pop());
				
				
		}catch(FileNotFoundException e){
			System.out.println("파일을 못찾음");
		}catch(IOException e){
			System.out.println("입출력 오류");
		}finally{
			try {
				fr.close();
				br.close();
			} catch (IOException e) {}	
		}
	}

}
