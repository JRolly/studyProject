

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestFinalVariable
{
	//定义成员变量时指定默认值，合法。
	final int a = 6;
	final String str;
	final int c;
	final static double d;
	//既没有指定默认值，又没有在初始化块、构造器中指定初始值，下面定义char属性是不合法的。
	//final char ch;
	//初始化块，可对没有指定默认值的实例属性指定初始值
	{
		//在初始化块中为实例属性指定初始值，合法
		str = "Hello";
		//定义a属性时已经指定了默认值，不能为a重新赋值，下面赋值语句非法
		//a = 9;
	}
	//静态初始化块，可对没有指定默认值的类属性指定初始值
	static
	{
		//在静态初始化块中为类属性指定初始值，合法
		d = 5.6;
	}
	//构造器，可对没有指定默认值、且没有在初始化块中指定初始值的实例属性指定初始值
	public TestFinalVariable()
	{
		//如果初始化块中已经对str指定了初始化值，构造器中不能再对final变量赋值，下面赋值语句非法
		//str = "java";
		c = 5;
	}
	public void changeFinal()
	{
		//普通方法不能为final修饰的成员变量赋值
		//d = 1.2;
		//不能在普通方法中为final成员变量指定初始值
		//ch = 'a';
	}
	public static void main(String[] args) 
	{
		TestFinalVariable tf = new TestFinalVariable();
		System.out.println(tf.a);
		System.out.println(tf.c);
		System.out.println(tf.d);
	}
}
