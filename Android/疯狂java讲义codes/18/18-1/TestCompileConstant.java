

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
class MyTest
{
	static
	{
		System.out.println("静态初始化块...");
	}
	//使用一个字符串直接量为static final属性赋值
	static final String comileConstant = 
		"Struts2权威指南";
//	//采用系统当前时间为static final属性赋值
//	static final String comileConstant = 
//		System.currentTimeMillis() + "";

}
public class TestCompileConstant
{
	public static void main(String[] args) 
	{
		//访问、输出MyTest中的comileConstant属性
		System.out.println(MyTest.comileConstant);
	}
}
