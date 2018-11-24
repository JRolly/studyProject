

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
class BaseClass
{
	public int a = 5;
}
class SubClass extends BaseClass
{
	public int a = 7;
	public void accessOwner()
	{
		System.out.println(a);
	}
	public void accessBase()
	{
		//通过super来访问方法调用者对应的父类对象
		System.out.println(super.a);
	}
	public static void main(String[] args)
	{
		SubClass sc = new SubClass();
		//直接访问SubClass对象的a属性将会输出7
		System.out.println(sc.a);
		//输出7
		sc.accessOwner();
		//输出5
		sc.accessBase();
	}
}