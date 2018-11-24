

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestGc
{
	private double height;
	public static void main(String[] args) 
	{
		for (int i = 0 ; i < 4; i++)
		{
			new TestGc();
			//System.gc();
			Runtime.getRuntime().gc();
		}
	}
	public void finalize()
	{
		System.out.println("系统正在清理TestGc对象的资源...");
	}
}
