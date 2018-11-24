
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
public class TestMatches
{
	public static void main(String[] args) 
	{
		String[] mails =
		{
			"kongyeeku@163.com" ,
			"kongyeeku@gmail.com",
			"ligang@oneedu.cn",
			"wawa@abc.xx"
		};
		String mailRegEx = "\\w{3,20}@\\w+\\.(com|org|cn|org|net|gov)";
		Pattern mailPattern = Pattern.compile(mailRegEx);
		Matcher matcher = null;
		for (String mail : mails)
		{
			if (matcher == null)
			{
				matcher = mailPattern.matcher(mail); 
			}
			else
			{
				matcher.reset(mail);
			}
			if (matcher.matches())
			{
				System.out.println(mail + "是一个有效的邮件地址！");
			}
			else
			{
				System.out.println(mail + "不是一个有效的邮件地址！");
			}
		}
	}
}