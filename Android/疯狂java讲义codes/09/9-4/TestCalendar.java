import java.util.*;
import static java.util.Calendar.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestCalendar
{
	public static void main(String[] args) 
	{
		Calendar c = Calendar.getInstance();
		//取出年
		System.out.println(c.get(YEAR));
		//取出月份
		System.out.println(c.get(MONTH));
		//取出日
		System.out.println(c.get(DATE));
		//分别设置年、月、日、小时、分钟、秒
		c.set(2003 , 10 , 23 , 12, 32, 23);//2003-11-23 12:32:23
		System.out.println(c.getTime());
		//将Calendar的年前推1年
		c.add(YEAR , -1); //2002-11-23 12:32:23
		System.out.println(c.getTime());
		//将Calendar的月前推8个月
		c.roll(MONTH , -8); //2002-03-23 12:32:23
		System.out.println(c.getTime());
	}
}
