
package yeeku;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestOutputProperty
{
	public static void main(String[] args) 
	{
		//访问另一个包中的Output接口的MAX_CACHE_LINE属性
		System.out.println(lee.Output.MAX_CACHE_LINE);
		//下面语句将引起"为final变量赋值"的编译异常：
		lee.Output.MAX_CACHE_LINE = 20;
	}
}
