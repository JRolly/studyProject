

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */

class Apple<T extends Number>
{
	T size;

	public Apple()
	{
	}

	public Apple(T size)
	{
		this.size = size;
	}

	public void setA(T size)
	{
		this.size = size;
	}
	public T getSize()
	{
		 return this.size;
	}
}

public class TestErasure
{
	public static void main(String[] args)
	{
		Apple<Integer> a = new Apple<Integer>(6);
		//a的getSize方法返回Integer对象
		Integer as = a.getSize();
		//把a对象赋给Apple变量，会丢失尖括号里的类型信息
		Apple b = a;
		//b只知道size的类型是Number
		Number size1 = b.getSize();
		//下面代码引起编译错误
		//Integer size2 = b.getSize();
	}
}