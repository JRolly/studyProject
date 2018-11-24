

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Cow
{
	private double weight;
	//外部类的两个重载的构造器
	public Cow(){}
	public Cow(double weight)
	{
		this.weight = weight;
	}
	//定义一个内部类
	private class CowLeg
	{
		//内部类的两个属性
		private double length;
		private String color;
		//内部类的两个重载的构造器
		public CowLeg(){}
		public CowLeg(double length , String color)
		{
			this.length = length;
			this.color = color;
		}
		public void setLength(double length)
		{
			this.length = length;
		}
		public double getLength()
		{
			 return this.length;
		}
		public void setColor(String color)
		{
			this.color = color;
		}
		public String getColor()
		{
			 return this.color;
		}
		//内部类方法
		public void info()
		{
			System.out.println("当前牛腿颜色是：" + color + ", 高：" + length);
			//直接访问外部类的private属性：weight
			System.out.println("本牛腿所在奶牛重：" + weight);
		}
	}
	public void test()
	{
		CowLeg cl = new CowLeg(1.12 , "黑白相间");
		cl.info();
	}
	public static void main(String[] args)
	{
		Cow cow = new Cow(378.9);
		cow.test();
	}
}