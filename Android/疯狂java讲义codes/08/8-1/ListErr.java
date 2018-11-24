
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
public class ListErr
{
	public static void main(String[] args) 
	{
		//创建一个只想保存字符串的List集合
		List strList = new ArrayList();
		strList.add("Struts2权威指南");
		strList.add("基于J2EE的Ajax宝典");
		strList.add("轻量级J2EE企业应用实战");
		//”不小心“把一个Integer对象”丢进"了集合
		strList.add(5);
		for (int i = 0; i < strList.size() ; i++ )
		{
			//因为List里取出的全部是Object，所以必须强制类型转换
			//最后一个元素将出现ClassCastException异常
			String str = (String)strList.get(i);
		}
	}
}