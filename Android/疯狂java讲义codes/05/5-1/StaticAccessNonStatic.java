

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class StaticAccessNonStatic
{
	public void info()
	{
		System.out.println("简单的info方法");
	}
	public static void main(String[] args) 
	{
		//因为main方法是静态方法，而info是非静态方法，所以下面语句将出现错误。
		info();
	}
}