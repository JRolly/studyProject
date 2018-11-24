

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestThreadException implements Runnable
{
	public void run()
	{
		firstMethod();
	}
	public void firstMethod()
	{
		secondMethod();
	}
	public void secondMethod()
	{
		int a = 5;
		int b = 0;
		int c = a / b;
	}
	public static void main(String[] args) 
	{
		new Thread(new TestThreadException()).start();
	}
}
