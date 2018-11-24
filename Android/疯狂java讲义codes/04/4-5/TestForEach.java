

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestForEach
{
	public static void main(String[] args) 
	{
		String[] books = {"轻量级J2EE企业应用实战" , 
			"Struts2权威指南",
			"基于J2EE的Ajax宝典"};
		//使用foreach循环来遍历数组元素，其中book将会自动迭代每个数组元素
		for (String book : books)
		{
			System.out.println(book);
		}
	}
}
