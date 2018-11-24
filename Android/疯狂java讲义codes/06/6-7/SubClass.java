

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class SubClass extends Out.In
{
	//显示定义SubClass的构造器
	public SubClass(Out out)
	{
		//通过传入的Out对象显式调用In的构造器
		out.super("hello");
	}
}
