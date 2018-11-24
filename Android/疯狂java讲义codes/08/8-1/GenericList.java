
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
public class GenericList
{
	public static void main(String[] args) 
	{
		//创建一个只想保存字符串的List集合
		List<String> strList = new ArrayList<String>();
		strList.add("Struts2权威指南");
		strList.add("基于J2EE的Ajax宝典");
		strList.add("轻量级J2EE企业应用实战");
		//下面代码将引起编译错误
		strList.add(5);
		for (int i = 0; i < strList.size() ; i++ )
		{
			//下面代码无需强制类型转换
			String str = strList.get(i);
		}
	}
}