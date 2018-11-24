
import java.io.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ReadTeacher
{
	public static void main(String[] args) 
	{
		ObjectInputStream ois = null;
		try
		{
			//创建一个ObjectInputStream输入流
			ois = new ObjectInputStream(
				new FileInputStream("teacher.txt"));
			//依次读取ObjectInputStream输入流中的四个对象
			Teacher t1 = (Teacher)ois.readObject();
			Teacher t2 = (Teacher)ois.readObject();
			Person p = (Person)ois.readObject();
			Teacher t3 = (Teacher)ois.readObject();
			//输出true
			System.out.println("t1的student引用和p是否相同："
				+ (t1.getStudent() == p));
			//输出true
			System.out.println("t2的student引用和p是否相同："
				+ (t2.getStudent() == p));
			//输出true
			System.out.println("t2和t3是否是同一个对象："
				+ (t2 == t3));
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
		finally
		{
			try
			{
				if (ois != null)
					ois.close();
			}
			catch (IOException ex)
			{
				ex.printStackTrace();
			}
		}
	}
}
