/**
	static	用于修饰成员
	当成员被静态修饰后，就多了一种调用方式，除了被对象调用，还可以直接被类名调用：
		类名.静态静态成员
	
	特点：
		随着类的加载而加载
		优先于对象存在
		被所有对象所共享
		可以直接被类名调用
	
	注意事项：
	静态方法只能访问静态成员
	静态方法中不可以定义this,super关键字
	
	好处：对对象的共享数据进行单独空间的存储，节省空间，
		  可以直接被类名调用
	坏处：生命周期太长
		  访问出现局限性
		  
	应用；
		每一个应用程序都有共性的功能，可以将这些功能封装，以便复用
*/

class ArrayTool
{
	public int getMax(int[] arr)
	{
		int max = 0;
		for (int x = 1; x < arr.length; x++)
		{
			if (arr[x] > arr[max])
				max = x;
		}
		return arr[max];
	}
}

class Person
{
	String name;
	static String country = "CN";
	public void show()
	{
		System.out.println(name+"::"+country);
	}
}

class StatiDemo
{
	public static void main(String[] args)
	{
		// Person p = new Person();
		// p.name = "lsff";
		// p.show();
		System.out.println(Person.country);
	}
}