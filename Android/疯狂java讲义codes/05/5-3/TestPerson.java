

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestPerson
{
	public static void main(String[] args) 
	{
		//Person类已经加载，则eyeNum变量起作用了，输出0
		System.out.println("Person的eyeNum类属性值:" + Person.eyeNum);
		//创建Person对象
		Person p = new Person();
		//通过Person对象的引用p来访问Person对象name实例属性
		//并通过实例访问eyeNum类属性
		System.out.println("p变量的name属性值是：" + p.name 
			+ " p对象的eyeNum属性值是：" + p.eyeNum);
		//直接为name实例属性赋值
		p.name = "孙悟空";
		//通过p访问eyeNum类属性，依然是访问Person的eyeNum属性
		p.eyeNum = 2;
		//再次通过Person对象来访问name实例属性和eyeNum类属性
		System.out.println("p变量的name属性值是：" + p.name 
			+ " p对象的eyeNum属性值是：" + p.eyeNum);
		//前面通过p修改了Person的eyeNum属性，此处的Person.eyeNum将输出2
		System.out.println("Person的eyeNum类属性值:" + Person.eyeNum);
		Person p2 = new Person();
		//p2访问的eyeNum类属性依然引用Person类的，因此依然输出2
		System.out.println("p2对象的eyeNum类属性值:" + p2.eyeNum);
	}
}
