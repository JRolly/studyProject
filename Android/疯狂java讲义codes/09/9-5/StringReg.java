
import java.util.regex.*; 
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

public class StringReg 
{
	public static void main(String[] args)
	{
		String[] msgs =
		{
			"Java has regular expressions in 1.4", 
			"regular expressions now expressing in Java", 
			"Java represses oracular expressions" 
		};
		for (String msg : msgs)
		{
			System.out.println(msg.replaceFirst("re\\w*" , "¹þ¹þ\1"));
			System.out.println(Arrays.toString(msg.split(" ")));
		}		
	} 
}
