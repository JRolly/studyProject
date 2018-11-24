
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
public class PrintStreamTest
{
	public static void main(String[] args)throws IOException
	{
		PrintStream ps = null;
		try
		{
			//创建一个节点输出流：FileOutputStream
			FileOutputStream fos = new FileOutputStream("test.txt");
			//以PrintStream来包装FileOutputStream输出流
			ps = new PrintStream(fos);
			//使用PrintStream执行输出
			ps.println("普通字符串");
			ps.println(new PrintStreamTest());
		}
		catch (IOException ioe)
		{
			ioe.printStackTrace(ps);
		}
		finally
		{
			ps.close();
		}
	}
}
