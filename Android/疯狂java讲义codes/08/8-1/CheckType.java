
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
//自定义一个StrList集合类，使用组合的方式来复用ArrayList类
class StrList
{
	private List strList = new ArrayList();
	//定义StrList的add方法
	public boolean add(String ele)
	{
		return strList.add(ele);
	}
	//重写get方法，将get方法的返回值类型改为String类型
	public String get(int index)
	{
		return (String)strList.get(index);
	}
	public int size()
	{
		return strList.size();
	}
}
public class CheckType
{
	public static void main(String[] args) 
	{
		//创建一个只想保存字符串的List集合
		StrList strList = new StrList();
		strList.add("Struts2权威指南");
		strList.add("基于J2EE的Ajax宝典");
		strList.add("轻量级J2EE企业应用实战");
		//下面语句不能把Integer对象“丢进”集合中,将引起编译异常
		strList.add(5);
		System.out.println(strList);
		for (int i = 0; i < strList.size() ; i++ )
		{
			//因为StrList里元素的类型就是String类型，所以无需强制类型转换
			String str = strList.get(i);
		}
	}
}