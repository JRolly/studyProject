
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
public class TestFinally
{
	public static void main(String[] args) 
	{
		FileInputStream fis = null;
		try
		{
			fis = new FileInputStream("a.txt");	
		}
		catch (IOException ioe)
		{
			System.out.println(ioe.getMessage());
			//return语句强制方法返回
			//return ;
			//使用exit来退出虚拟机
			System.exit(1);
		}
		finally
		{
			//关闭磁盘文件，回收资源
			if (fis != null)
			{
				try
				{
					fis.close();
				}
				catch (IOException ioe)
				{
					ioe.printStackTrace();
				}
			}
			System.out.println("程序已经执行了finally里的资源回收!");
		}
	}
}
