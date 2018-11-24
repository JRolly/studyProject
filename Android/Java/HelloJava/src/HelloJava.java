/**
 * 
 */

/**
 * @author Jaysi
 *
 */
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;


public class HelloJava {

	/**
	 * @param args
	 */	
	public void helloJava() {
		int arr[] = {4,5,3,6,2};
		
		//��������
		System.out.println("����ǰ�����飺");
		print(arr);
		Arrays.sort(arr);
		System.out.println("���������飺");
		print(arr);		
		
		System.out.println("�����ֵ5֮ǰ�����飺");
		print(arr);
		//�������
		Arrays.fill(arr,5);
		System.out.println("�����ֵ5֮������飺");
		print(arr);
		
		//�滻����Ԫ��
		Arrays.fill(arr,1,3,0);
		System.out.println("�滻�±�Ϊ1~3(������3)��Ԫ��Ϊ0֮������飺");
		print(arr);		
		
		//��������
		int newarr[] = Arrays.copyOf(arr,8);
		System.out.println("copyOf���Ƶ�����Ϊ��");
		print(newarr);
		int newarr1[] = Arrays.copyOfRange(arr,2,9);
		System.out.println("copyOfRange���Ƶ�����Ϊ��");
		print(newarr1);		
		
		//��ʽ������
		Date today = new Date();
		String en_mounth = String.format(Locale.US, "%tb",today); //��ʽ��Ϊ�·ݵ�Ӣ����д
		System.out.println("��ʽ������·�Ӣ����дΪ��"+en_mounth);
		//��ʽ��ʱ��
		Date date = new Date();
		System.out.println("Ĭ��ʱ���ʽΪ��"+date);
		System.out.println("24Сʱ��ʱ��Ϊ��"+String.format("%tH", date));
		//System.out.println("Ĭ������ʱ���ʽΪ��"+date);
		System.out.println("���ں�ʱ���ʽ����"+String.format("%tc", date));
	
		//������ʽ
		String s = "Mk00";
		
		boolean bs = s.matches("\\p{Upper}\\p{Lower}\\d\\d");
		System.out.println("s������ƥ����Ϊ��"+bs);
		boolean bs2 = s.matches("\\p{Upper}\\p{Lower}\\d{2}");
		System.out.println("s������ƥ����Ϊ��"+bs2);
		
		
		//StringBuilder
		StringBuilder builder = new StringBuilder("abcdefghijk");
		builder.delete(2, 5);
		System.out.println(builder);
		builder.append("l");
		System.out.println(builder);
		builder.insert(2,"cd");
		System.out.println(builder);
		
	}
	
	/*
	 * ��ӡ����
	 * */
	public static void print(int arr[])
	{
		//foreach���
		for(int e:arr)
		{
			System.out.println(e+"\t");
		}		
	}

}










