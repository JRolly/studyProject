

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public abstract class Shape
{
	{
		System.out.println("执行Shape的初始化块...");
	}

	private String color;
	//定义一个计算周长的抽象方法
	public abstract double calPerimeter();
	//定义一个返回形状的抽象方法
	public abstract String getType();

	//定义Shape的构造器，该构造器并不是用于创建Shape对象，而是用于被子类调用
	public Shape(){}
	public Shape(String color)
	{
		System.out.println("执行Shape的构造器...");
		this.color = color;
	}

	public void setColor(String color)
	{
		this.color = color;
	}
	public String getColor()
	{
		 return this.color;
	}
}