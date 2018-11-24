

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Apple extends Fruit
{
	public static void main(String[] args) 
	{
		//创建Apple的对象
		Apple a = new Apple();
		//Apple对象本身没有weight属性。
		//因为Apple的父类有weight属性，也可以访问Apple对象的属性。
		a.weight = 56;
		//调用Apple对象的info方法
		a.info();
	}
}
