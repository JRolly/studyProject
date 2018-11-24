

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestConstructor
{
	public String name;
	public int count;
	//提供自定义的构造器，该构造器包含两个参数
	public TestConstructor(String name , int count)
	{
		//构造器里的this代表它进行初始化的对象
		//下面两行代码将传入的2个参数赋给this代表对象的name和count属性
		this.name = name;
		this.count = count;
	}
	public static void main(String[] args)
	{
		//使用自定义的构造器来创建TestConstructor对象
		//系统将会对该对象执行自定义的初始化
		TestConstructor tc = new TestConstructor("Struts2权威指南" , 20000);
		//输出TestConstructor对象的name和count属性
		System.out.println(tc.name);
		System.out.println(tc.count);
	}
}
