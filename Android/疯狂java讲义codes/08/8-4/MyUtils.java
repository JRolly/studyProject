
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
public class MyUtils
{
	/*
	public static <T> void copy(Collection<T> dest , Collection< ? extends T> src)
	{
		for (T ele : src)
		{
			dest.add(ele);
		}
	}
	*/
	public static <T> T copy(Collection<? super T> dest , Collection<T> src)
	{
		T last = null;
		for (T ele  : src)
		{
			last = ele;
			dest.add(ele);
		}
		return last;
	}

	public static void main(String[] args) 
	{
		List<Number> ln = new ArrayList<Number>();
		List<Integer> li = new ArrayList<Integer>();
		li.add(5);
		Integer last = copy(ln , li);
		System.out.println(ln);

	}
}
