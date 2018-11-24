

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
class Base
{
	public double size;
	public String name;

	public Base(double size , String name)
	{
		this.size = size;
		this.name = name;
	}
}
public class Sub extends Base
{
	public String color;
	public Sub(double size , String name , String color)
	{
		//通过super调用来调用父类构造器的初始化过程
		super(size , name);
		this.color = color;
	}

	public static void main(String[] args)
	{
		Sub s = new Sub(5.6 , "测试对象" , "红色");
		//输出Sub对象的三个属性
		System.out.println(s.size + "--" + s.name + "--" + s.color);
	}
}
