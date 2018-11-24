

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestFinalMethod
{
	public static void test(){}
}

class Sub extends TestFinalMethod
{
	//下面方法定义将出现编译错误，不能重写final方法
	public void test(){}
}
