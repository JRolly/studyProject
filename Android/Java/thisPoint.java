/**
	this：用于区分局部变量和成员变量同名的情况
	this代表本类对象
	哪个对象在调用this所在的函数，this就代表哪个对象
*/
class Person
{
	private int age;
	private String name;
    Person()
    {
		age = 20;
        System.out.println("构造函数");
    }
	Person(String name)
	{
		this.name = name;
		System.out.println("A:name="+name);
	}
	Person(String s,int a)
	{
		name = s;
		age = a;
		System.out.println("A:name="+name+",age="+age);
	}
	
//this的应用：当定义类中功能时，该函数内部要用到调用该函数的对象时
//	这是用this来表示这个对象
// 本类功能内部使用到了本类对象，都用this表示
	public boolean cpmpare(Person p)
	{
		return this.age == p.age;	//p1调用是，this代表p1，p代p2
	}
}

class PersonDemo3
{
	public static void main(String[] args)
	{
		Person p1 = new Person(20);
		Person p2 = new Person(23);
		boolean b = p1.compare(p2);
		System.out.println(b);
		
		// Person p = new Person();
		// new Person();
		// Person p1 = new Person("Jack");
		// Person p2 = new Person("forsn");
	}
}

