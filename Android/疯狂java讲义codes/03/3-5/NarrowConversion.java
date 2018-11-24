

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class NarrowConversion
{
	public static void main(String[] args) 
	{
		int iValue = 233;
		//强制把一个int类型的值转换为byte类型的值
		byte bValue = (byte)iValue;
		//将输出-23
		System.out.println(bValue);
		double dValue = 3.98;
		//强制把一个double类型的值转换为int
		int toI = (int)dValue;
		// 将输出3
		System.out.println(toI);
	}
}
