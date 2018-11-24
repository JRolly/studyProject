import java.util.regex.*;
import java.io.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class JGrep 
{ 
	public static void main(String[] args) throws Exception
	{
		Pattern p = Pattern.compile("String"); 
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("JGrep.java")));
		String buffer = null;
		int count = 1;
		while((buffer = br.readLine()) != null)
		{ 
			Matcher m = p.matcher(buffer); 
			while(m.find()) 
				System.out.println(count + ": " + 
				m.group() + ": " + m.start() + ":" +  m.end());
			count++;
		} 
	} 
}