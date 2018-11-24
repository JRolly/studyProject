
import java.nio.*;
import java.nio.channels.*;

import java.io.*;

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class FileLockTest
{
	public static void main(String[] args) 
	{
		FileChannel channel = null;
		try
		{
			//使用FileOutputStream获取FileChannel
			channel = new FileOutputStream("a.txt")
				.getChannel();
			//使用非阻塞式方式对指定文件加锁
			FileLock lock = channel.tryLock();
			//程序暂停5s
			Thread.sleep(5000);
			//释放锁
			lock.release();
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
		finally
		{
			try
			{
				if (channel != null)
					channel.close();
			}
			catch (IOException ex)
			{
				ex.printStackTrace();
			}
		}
	}
}
