

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class PrintCommand implements Command
{
	public void process(int[] target)
	{
		for (int tmp : target )
		{
			System.out.println("迭代输出目标数组的元素:" + tmp);
		}
	}
}
