

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ReturnThis
{
	public int age;
	public ReturnThis grow()
	{
		age++;
		//return this，返回调用该方法的对象
		return this;
	}
	public static void main(String[] args)
	{
		ReturnThis rt = new ReturnThis();
		//可以连续调用同一个方法
		rt.grow()
		  .grow()
		  .grow();
		System.out.println("rt的age属性值是:" + rt.age);
	}
}
