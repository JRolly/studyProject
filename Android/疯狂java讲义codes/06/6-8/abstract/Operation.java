

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public enum Operation
{
	PLUS, MINUS, TIMES, DIVIDE;
	//为枚举类定义一个方法，用于实现不同的运算
	public double eval(double x, double y)
	{
		switch(this) 
		{
			case PLUS:   return x + y;
			case MINUS:  return x - y;
			case TIMES:  return x * y;
			case DIVIDE: return x / y;
			default: return 0;
		}
	}
	public static void main(String[] args)
	{
		System.out.println(Operation2.PLUS.eval(3, 4));
		System.out.println(Operation2.MINUS.eval(5, 4));
		System.out.println(Operation2.TIMES.eval(5, 4));
		System.out.println(Operation2.DIVIDE.eval(5, 4));
	}
}
