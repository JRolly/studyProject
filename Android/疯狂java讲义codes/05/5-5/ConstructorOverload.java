

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ConstructorOverload
{
	public String name;
	public int count;
	//提供无参数的构造器
	public ConstructorOverload()
	{
	}
	//提供带2个参数的构造器，对该构造器返回的Java对象执行初始化
	public ConstructorOverload(String name , int count)
	{
		this.name = name;
		this.count = count;
	}
	public static void main(String[] args)
	{
		//通过无参数构造器创建ConstructorOverload对象
		ConstructorOverload oc1 = new ConstructorOverload();
		//通过有参数构造器创建ConstructorOverload对象
		ConstructorOverload oc2 = new ConstructorOverload("轻量级J2EE企业应用实战", 18000);
		System.out.println(oc1.name + " " +  oc1.count);
		System.out.println(oc2.name + " " +  oc2.count);

	}
}
