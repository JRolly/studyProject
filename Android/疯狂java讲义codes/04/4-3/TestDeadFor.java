

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestDeadFor
{
	public static void main(String[] args) 
	{
		//省略了for循环三个部分，循环条件将一直为true
		for (; ; )
		{
			System.out.println("=============");
		}
	}
}
