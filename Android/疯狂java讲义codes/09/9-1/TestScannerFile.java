
import java.util.*;
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
public class TestScannerFile
{
	public static void main(String[] args) throws Exception
	{
		//将一个File对象作为Scanner的构造器参数，则Scanner读取文件内容
		Scanner sc = new Scanner(new File("a.txt"));
		System.out.println("a.txt文件内容如下：");
		//判断是否还有下一行
		while(sc.hasNextLine())
		{
			//输出文件中的一行
			System.out.println(sc.nextLine());
		}
	}
}
