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
public class AppendContent
{
	public static void main(String[] args) 
	{
		RandomAccessFile raf = null;
		try
		{
			//以读、写方式打开一个RandomAccessFile对象
			raf = new RandomAccessFile("out.txt" , "rw");
			//将记录指针移动的out.txt文件的最后
			raf.seek(raf.length());
			raf.write("追加的内容！\r\n".getBytes());
		}
		catch (IOException ex)
		{
			ex.printStackTrace();
		}
		finally
		{
			try
			{
				if (raf != null)
				{
					raf.close();
				}
			}
			catch (IOException ex)
			{
				ex.printStackTrace();
			}
		}

	}
}
