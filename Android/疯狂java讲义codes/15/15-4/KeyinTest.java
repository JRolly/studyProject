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
public class KeyinTest
{
	public static void main(String[] args) 
	{
		BufferedReader br = null;
		try
		{
			//将Sytem.in对象转换成Reader对象
			InputStreamReader reader = new InputStreamReader(System.in);
			//将普通Reader包装成BufferedReader
			br = new BufferedReader(reader);
			String buffer = null;
			//采用循环方式来一行一行的读取
			while ((buffer = br.readLine()) != null)
			{
				//如果读取的字符串为"exit"，程序退出
				if (buffer.equals("exit"))
				{
					System.exit(1);
				}
				//打印读取的内容
				System.out.println("输入内容为:" + buffer);
			}
		}
		catch (IOException ioe)
		{
			ioe.printStackTrace();
		}
		//关闭输入流
		finally
		{
			try
			{
				br.close();				
			}
			catch (IOException ioe)
			{
				ioe.printStackTrace();
			}
		}
	}
}
