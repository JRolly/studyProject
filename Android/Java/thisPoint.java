/**
	this���������־ֲ������ͳ�Ա����ͬ�������
	this���������
	�ĸ������ڵ���this���ڵĺ�����this�ʹ����ĸ�����
*/
class Person
{
	private int age;
	private String name;
    Person()
    {
		age = 20;
        System.out.println("���캯��");
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
	
//this��Ӧ�ã����������й���ʱ���ú����ڲ�Ҫ�õ����øú����Ķ���ʱ
//	������this����ʾ�������
// ���๦���ڲ�ʹ�õ��˱�����󣬶���this��ʾ
	public boolean cpmpare(Person p)
	{
		return this.age == p.age;	//p1�����ǣ�this����p1��p��p2
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

