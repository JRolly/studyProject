

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
interface Product
{
	public double getPrice();
	public String getName();
}
public class TestAnonymous
{
	public void test(Product p)
	{
		System.out.println("购买了一个" + p.getName() + "，花掉了" + p.getPrice());
	}
	public static void main(String[] args) 
	{
		TestAnonymous ta = new TestAnonymous();
		//调用test方法时，需要传入一个Product参数，此处传入其匿名实现类的实例
		ta.test(new Product()
		{
			public double getPrice()
			{
				return 567.8;
			}
			public String getName()
			{
				return "AGP显卡";
			}
		});
	}
}
