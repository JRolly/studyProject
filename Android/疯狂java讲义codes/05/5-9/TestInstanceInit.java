

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestInstanceInit
{
	//先执行初始化块将a属性赋值为6
	{
		a = 6;
	}
	//再执行将a属性赋值为9
	int a = 9;
	public static void main(String[] args) 
	{
		//下面代码将输出9。
		System.out.println(new TestInstanceInit().a);
	}
}
