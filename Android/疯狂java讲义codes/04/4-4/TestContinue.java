

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestContinue
{
	public static void main(String[] args) 
	{
		//一个简单的for循环
		for (int i = 0; i < 3 ; i++ )
		{
			System.out.println("i的值是" + i);
			if (i == 1)
			{
				continue;
			}
			System.out.println("continue后的输出语句");
		}
	}
}
