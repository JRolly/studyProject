
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
public class TestSimpleDateFormat
{
	public static void main(String[] args) throws Exception
	{
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM的三岁的发送到dd日 HH时mm分ss秒"); 
		System.out.println(sdf.format(new Date()));

		String dateStr = "吞吞吐吐2007%12%03";
		//下面创建转换用的SimpleDateFormat时，需要转换字符串使用占位符替换，不需要转换的就照写
		SimpleDateFormat sdf2 = new SimpleDateFormat("吞吞吐吐yyyy%MM%dd");
		System.out.println(sdf2.parse(dateStr));

	}
}
