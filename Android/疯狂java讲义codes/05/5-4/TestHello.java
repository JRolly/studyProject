package lee;

import lee.sub.Apple;
import java.util.*;
import java.sql.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestHello
{
	public static void main(String[] args) 
	{
		Hello h = new Hello();
		//使用这种类全名
		lee.sub.Apple a = new lee.sub.Apple();
		//如果使用import语句来导入Apple类后，就可以不再使用类全名
		Apple aa = new Apple();
		Date d = new Date();
	}
}
