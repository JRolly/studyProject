

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestTeachableProgrammer
{
	public static void main(String[] args) 
	{
		TeachableProgrammer tp = new TeachableProgrammer("李刚");
		//直接调用TeachableProgrammer类从Programmer类继承到的work方法
		tp.work();
		//表面上调用的是Closure的work方法，实际上是回调TeachableProgrammer的teach方法
		tp.getCallbackReference().work();
	}
}
