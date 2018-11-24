

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
class SelfException extends Exception
{
	SelfException(){}
	SelfException(String msg)
	{
		super(msg);
	}
}
public class TestPrintStackTrace
{
	public static void main(String[] args)throws SelfException
	{
		firstMethod();
	}
	public static void firstMethod()throws SelfException
	{
		secondMethod();
	}
	public static void secondMethod()throws SelfException
	{
		thirdMethod();
	}
	public static void thirdMethod()throws SelfException
	{
		throw new SelfException("自定义异常信息");
	}
}
