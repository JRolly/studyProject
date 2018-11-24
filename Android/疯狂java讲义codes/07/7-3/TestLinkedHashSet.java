
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


public class TestLinkedHashSet
{
	public static void main(String[] args) 
	{
		LinkedHashSet books = new LinkedHashSet();
		books.add("Struts2权威指南");
		books.add("轻量级J2EE企业应用实战");
		//删除 Struts2权威指南
		books.remove("Struts2权威指南");
		//重新添加 Struts2权威指南
		books.add("Struts2权威指南");
		System.out.println(books);
	}
}