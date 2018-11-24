

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class NullAccessStatic
{
	private static void test()
	{
		System.out.println("静态方法");
	}
	public static void main(String[] args) 
	{
		//定义一个NullAccessStatic变量，其值为null
		NullAccessStatic nas = null;
		//null对象调用所属类的静态方法
		nas.test();
	}
}
