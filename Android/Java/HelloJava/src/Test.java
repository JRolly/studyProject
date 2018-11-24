import java.util.Arrays;


public class Test
{
	Test()
	{
		a = 32;
		b = 12;
		System.out.println("父类构造方法...");
	}
	
	Test(int i, int j)
	{
		a = i;
		b = j;
	}
	
	public int a, b;
	public void test()
	{
		System.out.println("父类test方法");
		int[] arra = new int[5];
		int[] arrb = new int[5];
		
		Arrays.fill(arra, 1);
		Arrays.fill(arrb, 1);
		
		System.out.println("arra =? arrb: " + Arrays.equals(arra, arrb));
		
		int[] arrc = {3,5,2,1,4};
		ShowArr(arrc);
		
		Arrays.sort(arrc);
		ShowArr(arrc);
		
		System.out.println("the index of 3 is:" + Arrays.binarySearch(arrc, 3));
		
		int[] arrd = Arrays.copyOf(arrc, 3);
		System.out.println(Arrays.toString(arrd));
			
		param(11,23);
		
		swap();
		System.out.println(a + " " + b);
		
	}
	
	void swap()
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	public void param(int ... INT)
	{
		for(int e: INT)
		{
			System.out.println(e + " ");
		}
	}
	
	public void ShowArr(int[] arr)
	{
		for(int e: arr)
		{
			System.out.println(e);
		}
	}
}

class TestChild extends Test
{
	int c;
	public TestChild() {
		// TODO Auto-generated constructor stub
		super();
		c = 33;
		//test();
		super.test();
		System.out.println(c);
	}
	
	public void test()
	{
		System.out.println("子类中覆盖的test方法...");
	}
	
	public void child()
	{
		System.out.println("子类child方法。。。");
	}
}

class Simple
{
	private static Simple instance;

	private Simple()
	{
		System.out.println("Simple类私有构造器");
	}
	
	public static Simple GetInstance()
	{
		if (instance != null)
		{
			instance = new Simple();
		}
		return instance;
	}	
}

class TypeBox
{
	public void TestTypeBox()
	{
		Character c = 'c';
		Byte nByte = 0x0;		
		Short nShort = 1;
		Integer integer = 2;
		Long nLong = 4l;
		Float f = 5.5f;
		Double lf = 6.6;
		Boolean b = true;
		
		System.out.println(c + " " + nByte + " " + nShort + " "
					+ integer + " " + nLong + " " + f + " " + lf + " " + b);
		
		String lfstr = "34.532";
		double d = Double.parseDouble(lfstr);
		System.out.println(d);
		
		d = 1111.2222;
		System.out.println(String.valueOf(d));
		
	}
}

class CacheClass
{
	private static int pos = 0;
	private static CacheClass[] cache = new CacheClass[10];
	private String name;
	
	public CacheClass(String name)
	{
		this.name = name;
	}
	
	public String getName()
	{
		return name;
	}
	
	public static CacheClass ValueOf(String name)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (cache[i] != null && cache[i].getName() == name)
			{
				return cache[i];
			}
		}
		
		++pos;
		if (pos == 10)
		{
			pos = 0;
		}
		cache[pos] = new CacheClass(name);
		return cache[pos];
	}
	
	public boolean equals(Object obj)
	{
		if (obj instanceof CacheClass)
		{
			CacheClass c = (CacheClass)obj;
			if (name.equals(c.getName()))
			{
				return true;
			}
		}
		return false;
	}
	
	public int hashCode()
	{
		return name.hashCode();
	}
}

abstract class AbstractClass
{
	private String name;
	private int age;
	
	public AbstractClass(String name, int age)
	{
		this.name = name;
		this.age = age;
	}
	
	protected void setName(String name)
	{
		this.name = name;
	}
	
	public String getName()
	{
		return name;
	}
	
	protected abstract void changeName(String name);

	public String toString()
	{
		return "AbstractClass[" + "name:" + name + " age:" + age + "]";
	}
}

class ChildAbsClass extends AbstractClass
{
	public ChildAbsClass(String name, int age)
	{
		super(name, age);		
	}
	
	public void changeName(String name)
	{
		this.setName(name);
	}
	
}





































