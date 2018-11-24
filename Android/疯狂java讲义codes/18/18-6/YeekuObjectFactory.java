
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
public class YeekuObjectFactory
{
	public static Object getInstance(String clsName)
	{
		try
		{
			//创建指定类对应的Class对象
			Class cls = Class.forName(clsName);
			//返回使用该Class对象所创建的实例
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
		//获取实例后需要强制类型转换
		Date d = (Date)YeekuObjectFactory.getInstance("java.util.Date");
		JFrame f = (JFrame)YeekuObjectFactory.getInstance("java.util.Date");
	}
}
