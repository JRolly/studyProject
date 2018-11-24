
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
public class PushbackTest
{
	public static void main(String[] args) 
	{
		PushbackReader pr = null;
		try
		{
			//创建一个PushbackReader对象，指定推回缓冲区的长度为64
			pr = new PushbackReader(new FileReader("PushbackTest.java") , 64);
			char[] buf = new char[32];
			//用以保存上次读取的字符串内容
			String lastContent = "";
			int hasRead = 0;
			//循环读取文件内容
			while ((hasRead = pr.read(buf)) > 0)
			{
				//将读取的内容转换成字符串
				String content = new String(buf , 0 , hasRead);
				int targetIndex = 0;
				//将上次读取的字符串和本次读取的字符串拼起来，查看是否包含目标字符串
				//如果包含目标字符串
				if ((targetIndex = (lastContent + content).indexOf("new PushbackReader")) > 0)
				{
					//将本次内容和上次内容一起推回缓冲区
					pr.unread((lastContent + content).toCharArray());
					//再次读取指定长度的内容（就是目标字符串之前的内容）
					pr.read(buf , 0 , targetIndex);
					//打印读取的内容
					System.out.print(new String(buf , 0 ,targetIndex));
					System.exit(0);
				}
				else
				{
					//打印上次读取的内容
					System.out.print(lastContent);
					//将本次内容设为上次读取的内容
					lastContent = content;
				}
			}
		}
		catch (IOException ioe)
		{
			ioe.printStackTrace();
		}
		finally
		{
			try
			{
				if (pr != null)
					pr.close();
			}
			catch (IOException ioe)
			{
				ioe.printStackTrace();
			}
		}
	}
}
