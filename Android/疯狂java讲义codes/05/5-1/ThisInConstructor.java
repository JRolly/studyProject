

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ThisInConstructor
{
	//定义一个名为foo的属性
	public int foo;
	public ThisInConstructor()
	{
		//在Test构造器里定义一个foo变量
		int foo = 0;
		//使用this代表此构造器刚刚创建的对象
		//下面的代码将会把刚创建对象的foo属性设置为6。
		this.foo = 6;
	}
	public static void main(String[] args)
	{
		//所有使用ThisInConstructor创建的对象的foo属性
		//都将被设为6，所以下面代码将输出6。
		System.out.println(new ThisInConstructor().foo);
	}
}
