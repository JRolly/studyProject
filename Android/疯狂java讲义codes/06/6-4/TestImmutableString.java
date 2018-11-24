

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestImmutableString
{
	public static void main(String[] args) 
	{
		String str1 = new String("Hello");
		String str2 = new String("Hello");
		//输出false
		System.out.println(str1 == str2);
		//输出true
		System.out.println(str1.equals(str2));
		//下面两此输出的hashCode相同
		System.out.println(str1.hashCode());
		System.out.println(str2.hashCode());
	}
}
