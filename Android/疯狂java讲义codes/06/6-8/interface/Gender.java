
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public enum Gender implements GenderDesc
{
	//此处的枚举值必须调用对应构造器来创建
	MALE("男")
	{
		public void info()
		{
			System.out.println("这个枚举值代表男性");
		}
	},
	FEMALE("女")
	{	
		public void info()
		{
			System.out.println("这个枚举值代表女性");
		}
	};
	private String name;
	//枚举类的构造器只能使用private修饰
	private Gender(String name)
	{
		this.name = name;
	}
	public String getName()
	{
		 return this.name;
	}
	/*
	public void info()
	{
		System.out.println("这是一个用于用于定义性别属性的枚举类");
	}
	*/
}