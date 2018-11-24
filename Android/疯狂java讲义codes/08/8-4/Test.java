
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
public class Test
{
	//声明一个泛型方法，该泛型方法中带一个T形参
//	static <T> void test(Collection<T> a, Collection<T> c)
	static <T> void test(Collection<? extends T> a, Collection<T> c)

	{
		for (T o : a)
		{
			c.add(o);
		}
	}
	public static void main(String[] args) 
	{
		List<Object> ao = new ArrayList<Object>();
		List<String> as = new ArrayList<String>();
		//下面代码将产生编译错误
		test(as , ao);
	}
}
