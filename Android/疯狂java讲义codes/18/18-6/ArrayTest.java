
import java.lang.reflect.*;
/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class YeekuArray extends Array
{
	public static T[] newInstance(Class<T> componentType, int length) 
	{
		return (T[])super.newInstance(componentType , length);
	}


	public static void main(String[] args) 
	{
		System.out.println(String[].class);
	}
}
