

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestScope2
{
	public static void main(String[] args) 
	{
		//定义一个方法局部变量作为循环变量
		int i;
		for ( i = 0 ; i < 10 ; i++)
		{
			System.out.println("Hello");
		}
	}
}
