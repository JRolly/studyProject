
import java.util.*;
import java.text.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestDataFormat
{
	public static void main(String[] args) throws Exception
	{
		/*
			DateFormat的构造器是protected的 但它提供了一些静态方法来获取DateFormat实例。
			df = new DateFormat();
			getDateInstance － 格式化后的字符串只有日期。
			getTimeInstance － 格式化的字符串只有时间
			getDateTimeInstance － 格式化的的字符串有日期、时间

		*/
		Date d = new Date();
		System.out.println(d);
		//为了程序更加友好的界面，要求把Date转换成一个符合Locale的字符串。

		DateFormat df = DateFormat.getDateTimeInstance(DateFormat.FULL, DateFormat.FULL, Locale.getDefault()); 
		System.out.println(df.format(d));

		String dateStr = "2007年aa月20日 星期二 上午11时54分15秒 CST";
		System.out.println(df.parse(dateStr));

	}
}
