
import java.util.regex.*; 

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */

public class StartEnd 
{ 
	public static void main(String[] args)
	{
		String regStr = "Java is very easy!";
		System.out.println("目标字符串是：" + regStr);
		Matcher m = Pattern.compile("\\w+") 
			.matcher(regStr); 
		while(m.find())
		{
			System.out.println(m.group() + "子串的起始位置：" + m.start()
				+ "，其结束位置：" + m.end()); 
		}
	} 
}
