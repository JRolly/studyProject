

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
//定义自己的异常处理器
class MyExHandler implements Thread.UncaughtExceptionHandler 
{
	//实现uncaughtException方法，该方法将处理线程的未处理异常
	public void uncaughtException(Thread t, Throwable e)
	{
		System.out.println(t + " 线程出现了异常：" + e);
	} 
}
public class ExHandler
{
	public static void main(String[] args) 
	{
		//设置主线程的异常处理器
		Thread.currentThread().setUncaughtExceptionHandler(
			new MyExHandler());
		int a = 5 / 0;
	}
}
