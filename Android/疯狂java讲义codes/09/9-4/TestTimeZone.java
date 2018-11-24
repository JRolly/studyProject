
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
public class TestTimeZone
{
	public static void main(String[] args) 
	{
		//取得Java所支持的所有时区ID
		String[] ids = TimeZone.getAvailableIDs();
		System.out.println(Arrays.toString(ids));
		TimeZone my = TimeZone.getDefault();
		//获取系统默认时区的ID:Asia/Shanghai
		System.out.println(my.getID());
		//获取系统默认时区的名称：中国标准时间
		System.out.println(my.getDisplayName());
		//获取指定ID的时区的名称：纽芬兰标准时间
		System.out.println(TimeZone.getTimeZone("CNT").getDisplayName());
	}
}
