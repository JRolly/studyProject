import javax.xml.crypto.dsig.spec.C14NMethodParameterSpec;

public class Main
{
	public static void main(String[] args)
	{
//		Cat cat = new Cat();
//		cat.speak();
//		
//		Dog dog = new Dog();
//		dog.speak();
		
//		Test t = new Test();
//
//		TestChild tc = new TestChild();
//		
//		System.out.println(tc instanceof TestChild);
		
//		Simple s1 = Simple.GetInstance();
//		Simple s2 = Simple.GetInstance();
//		System.out.println(s1 == s2);
//		
//		TypeBox tb = new TypeBox();
//		tb.TestTypeBox();
		
//		CacheClass cl = CacheClass.ValueOf("cache1");
//		CacheClass c2 = CacheClass.ValueOf("cache1");
//		System.out.println(cl == c2);
		
		ChildAbsClass cas = new ChildAbsClass("Susan", 21);
		System.out.println(cas.toString());
		cas.changeName("Ailis");
		System.out.println(cas.toString());
		
		
	}
}

















