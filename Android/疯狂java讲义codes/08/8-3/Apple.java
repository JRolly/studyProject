
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
public class Apple<T extends Number>
{
	T col;
	
	public static void main(String[] args)
	{
		Apple<Integer> ai = new Apple<Integer>();
		Apple<Double> ad = new Apple<Double>();
		//下面代码将引起编译异常
		//因为String类型传给T形参，但String不是Number的子类型。
		Apple<String> as = new Apple<String>();
		
	}
}
