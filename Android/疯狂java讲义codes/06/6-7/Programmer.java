

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */

interface Teachable
{
	void work();
}
public class Programmer
{
	private String name;
	//Programmer类的两个构造器
	public Programmer(){}
	public Programmer(String name)
	{
		this.name = name;
	}
	public void setName(String name)
	{
		this.name = name;
	}
	public String getName()
	{
		return this.name;
	}
	public void work()
	{
		System.out.println(name + "在灯下认真敲键盘...");
	}
}
