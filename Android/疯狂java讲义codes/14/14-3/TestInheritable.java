

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
//使用@Inheritable修饰的Base类
@Inheritable
class Base
{
}
//TestInheritable类只是继承了Base类，
//并未直接使用@Inheritable Annotiation修饰
public class TestInheritable extends Base
{
	public static void main(String[] args)
	{
		//打印TestInheritable类是否具有Inheritable Annotation
		System.out.println(TestInheritable.class 
			.isAnnotationPresent(Inheritable.class));
	}
}
