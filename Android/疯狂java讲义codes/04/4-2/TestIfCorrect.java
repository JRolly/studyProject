

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestIfCorrect
{
	public static void main(String[] args) 
	{
		int age = 45;
		if (age > 60)
		{
			System.out.println("老年人");
		}
		else if (age > 40 && !(age >60))
		{
			System.out.println("中年人");
		}
		else if (age > 20 && !(age > 60) && !(age > 40 && !(age >60)))
		{
			System.out.println("青年人");
		}			
	}
}
