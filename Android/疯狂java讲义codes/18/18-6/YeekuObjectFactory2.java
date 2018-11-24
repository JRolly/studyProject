
import java.util.*;
import javax.swing.*;
/**
 * Description:
 * <br/>Copyright (C), 2008-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class YeekuObjectFactory2
{
	public static <T> T getInstance(Class<T> cls)
	{
		try
		{
			return cls.newInstance();
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return null;
		}
	}
	public static void main(String[] args)
	{
		//获取实例后无需类型转换
		Date d = YeekuObjectFactory2.getInstance(Date.class);
		JFrame f = YeekuObjectFactory2.getInstance(JFrame.class);
	}
}
