

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Outer
{
	private int outProp = 9;
	class Inner
	{
		private int inProp = 5;
		public void acessOuterProp()
		{
			//内部类可以直接访问外部类的成员
			System.out.println("外部类的outProp属性值:" + outProp);
		}
	}
	public void accessInnerProp()
	{
		//外部类不能直接访问内部类属性,下面代码出现编译错误
		//System.out.println("内部类的inProp属性值:" + inProp);
		//如需访问内部类成员，必须显式创建内部类对象
		System.out.println("内部类的inProp属性值:" + new Inner().inProp);

	}
	public static void main(String[] args)
	{
		//执行下面代码，只创建了外部类对象，还未创建内部类对象
		Outer out = new Outer();
	}
}
