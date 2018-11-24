

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Test
{

	static
	{
		//使用静态初始化块为b变量指定出初始值
		b = 6;
		System.out.println("----------");
	}
	//声明a变量时指定初始值
	static int a = 5;
	static int b = 9;
	static int c;

	public static void main(String[] args)
	{
		System.out.println(Test.b);
	}

}
