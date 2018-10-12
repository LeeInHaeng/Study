package chap8_silsub1;

import java.io.*;

public class silsub1 {

	public static void dir(File fd){
		String[] filenames = fd.list();
		
		for(String fn : filenames){
			File f = new File(fd,fn);
			long t = f.lastModified();
			System.out.print(fn);
			System.out.print("\t파일 크기: "+f.length());
			System.out.printf("\t수정한 시간: %tb %tb %ta %tT\n", t,t,t,t);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		File f1 = new File(".");
		dir(f1);
		// 문제1 끝
		
		File f2 = new File(".\\tmp");

		if(!f2.exists()) // 현재 디렉토리 아래에 tmp라는 폴더가 없으면
		{
			if(!f2.mkdir()) // tmp 디렉토리를 만듦
				System.out.println("디렉토리 생성 실패");
		}
		
		FileWriter fw = null;
		BufferedWriter bw = null;
		String[] filenames = f1.list();
		
		try{
			File file = File.createTempFile("tmp", ".txt", f2);
			fw = new FileWriter(file);
			bw = new BufferedWriter(fw,50);
			
			for(String s : filenames){
				File f = new File(f1,s);
				long t = f.lastModified();
				bw.write(s);
				bw.write("\t파일크기: "+f.length());
				bw.write("\t수정한 시간: " + t + "\r\n");
			}
			
		}catch(IOException e){
			System.out.println("임시 파일 생성 오류");
		}finally{
			
			try {
				fw.close();
				bw.close();
			} catch (IOException e) {

			}
			
		}
		
		
	}

}
