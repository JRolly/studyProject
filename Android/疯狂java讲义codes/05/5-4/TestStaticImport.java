import static java.lang.System.*;
import static java.lang.Math.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestStaticImport
{
	public static void main(String[] args) 
	{
		//out是java.lang.System类的静态属性，代表标准输出
		//PI是java.lang.Math类的静态属性，表示常量
		out.println(PI);
	}
}
