
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
public class TestForeach
{
	public static void main(String[] args) 
	{
		//创建一个集合
		Collection books = new HashSet();
		books.add(new String("轻量级J2EE企业应用实战"));
		books.add(new String("Struts2权威指南"));
		books.add(new String("基于J2EE的Ajax宝典"));
		for (Object obj : books)
		{
			String book = (String)obj;
			System.out.println(book);
			if (book.equals("Struts2权威指南"))
			{
				//下面代码会引发ConcurrentModificationException异常
				books.remove(book);
			}
		}
		System.out.println(books);
	}
}
