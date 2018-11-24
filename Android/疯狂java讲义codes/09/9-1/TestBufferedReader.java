
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
public class TestBufferedReader
{
	public static void main(String[] args) throws Exception
	{
		//以System.in节点流，创建一个BufferedReader对象
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String buffer = null;
		//逐行读取键盘输入
		while ((buffer = br.readLine()) != null)
		{
			System.out.println("用户键盘输入是:" + buffer);
		}
	}
}
