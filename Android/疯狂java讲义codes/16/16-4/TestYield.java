

/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestYield extends Thread
{
	public TestYield()
	{
	}
	public TestYield(String name)
	{
		super(name);
	}
	//定义run方法作为线程执行体
	public void run()
	{
		for (int i = 0; i < 50 ; i++ )
		{
			System.out.println(getName() + "  " + i);
			//当i等于20时，使用yield方法让当前线程让步
			if (i == 20)
			{
				Thread.yield();
			}
		}
	}
    public static void main(String[] args) throws Exception
    {
		//启动两条并发线程
		TestYield ty1 = new TestYield("高级");
		//将ty1线程设置成最高优先级
		ty1.setPriority(Thread.MAX_PRIORITY);
		ty1.start();
		TestYield ty2 = new TestYield("低级");
		//将ty1线程设置成最低优先级
		ty2.setPriority(Thread.MIN_PRIORITY);
		ty2.start();	
    }
}