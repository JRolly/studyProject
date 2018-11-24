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
	public void test(List<Object> c) 
	{
		for (int i = 0; i < c.size(); i++) 
		{
			System.out.println(c.get(i)); 
		}
	}

	public static void main(String[] args) 
	{
		List<String> strList = new ArrayList<String>();
		Test t = new Test();
		t.test(strList);
	}
}
