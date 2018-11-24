

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestCommand
{
	public static void main(String[] args) 
	{
		ProcessArray pa = new ProcessArray();
		int[] target = {3, -4, 6, 4};
		//第一次处理数组，具体处理行为取决于PrintCommand
		pa.process(target , new PrintCommand());
		System.out.println("------------------");
		//第二次处理数组，具体处理行为取决于AddCommand
		pa.process(target , new AddCommand());
	}
}
