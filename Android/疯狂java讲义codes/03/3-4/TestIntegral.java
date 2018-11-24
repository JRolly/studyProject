

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestIntegral
{
	public static void main(String[] args) 
	{
		//下面代码是正确的，系统会自动把56当成byte类型处理
		byte a = 56;
		/*
		下面代码是错的，系统不会把9223372036854775807当成long类型处理，
		所以超出int的表数范围，从而引起错误
		*/
		//long bigValue = 9999999999999;
		//下面代码是正确的，在巨大的整数常量后使用L后缀，强制使用long类型
		long bigValue2 = 9223372036854775807L;
	
		//以0开头的整数常量是8进制的整数
		int octalValue = 013;
		System.out.println(octalValue);
		//以0x或0X开头的整数常量是16进制的整数
		int hexValue1 = 0x13;
		int hexValue2 = 0XaF;

		System.out.println(hexValue1);
		System.out.println(hexValue2);


	}
}
