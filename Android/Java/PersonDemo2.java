/*
    构造函数
	对象一建立就会调用对应的构造函数
	可以用于给对象进行初始化
    
	当一个类中没有定义构造函数时，那么系统会给该类加一个空参数的构造函数
	
	构造代码块是给所有对象进行统一初始化
*/

class Person
{
	private int age;
	private String name;
    Person()
    {
        System.out.println("构造函数");
    }
	Person(String s)
	{
		name = s;
		System.out.println("A:name="+name+",age="+age);
	}
}

class PersonDemo2
{
	public static void main(String[] args)
	{
		Person p = new Person();
		new Person();
		Person p1 = new Person("Jack");
	}
}