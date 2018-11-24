import java.util.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestErasure2
{
	public static void main(String[] args) 
	{
		List<Integer> li = new ArrayList<Integer>();
		li.add(6);
		li.add(9);
		List list = li;
		//下面代码引起“未经检查的转换”的警告，编译、运行时完全正常
		List<String> ls = list;
		//但只要访问ls里的元素，如下面代码将引起运行时异常。
		System.out.println(ls.get(0));
	}
}
