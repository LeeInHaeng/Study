package chap8_silsub1;

import java.io.*;

public class silsub1 {

	public static void dir(File fd){
		String[] filenames = fd.list();
		
		for(String fn : filenames){
			File f = new File(fd,fn);
			long t = f.lastModified();
			System.out.print(fn);
			System.out.print("\t���� ũ��: "+f.length());
			System.out.printf("\t������ �ð�: %tb %tb %ta %tT\n", t,t,t,t);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		File f1 = new File(".");
		dir(f1);
		// ����1 ��
		
		File f2 = new File(".\\tmp");

		if(!f2.exists()) // ���� ���丮 �Ʒ��� tmp��� ������ ������
		{
			if(!f2.mkdir()) // tmp ���丮�� ����
				System.out.println("���丮 ���� ����");
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
				bw.write("\t����ũ��: "+f.length());
				bw.write("\t������ �ð�: " + t + "\r\n");
			}
			
		}catch(IOException e){
			System.out.println("�ӽ� ���� ���� ����");
		}finally{
			
			try {
				fw.close();
				bw.close();
			} catch (IOException e) {

			}
			
		}
		
		
	}

}
