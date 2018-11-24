

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestBitOperator
{
	public static void main(String[] args) 
	{
		//将输出1
		System.out.println(5 & 9);
		//将输出13
		System.out.println(5 | 9);
		//将输出4
		System.out.println(~-5);
		//将输出12
		System.out.println(5 ^ 9);
		//输出20
		System.out.println(5 << 2);
		//输出-20
		System.out.println(-5 << 2);
		//输出-2
		System.out.println(-5 >> 2);
		//输出1073741822
		System.out.println(-5 >>> 2);
	}
}
