

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
class Name
{
	private String firstName;
	private String lastName;

	public Name(){}

	public Name(String firstName , String lastName)
	{
		this.firstName = firstName;
		this.lastName = lastName;
	}

	public void setFirstName(String firstName)
	{
		this.firstName = firstName;
	}
	public String getFirstName()
	{
		 return this.firstName;
	}

	public void setLastName(String lastName)
	{
		this.lastName = lastName;
	}
	public String getLastName()
	{
		 return this.lastName;
	}

}
public class Person
{
	private final Name name;

	public Person(Name name)
	{
		//this.name = name;
		this.name = new Name(name.getFirstName(), name.getLastName());
	}
	public Name getName()
	{
		//return name;
		return new Name(name.getFirstName(), name.getLastName());
	}
	public static void main(String[] args)
	{
		Name n = new Name("悟空", "孙");
		Person p = new Person(n);
		//如果没有保护：Person对象的Name属性的firstName属性值为"悟空"
		System.out.println(p.getName().getFirstName());
		//改变Person对象Name属性的firstName属性值
		n.setFirstName("八戒");
		//如果没有保护：Person对象的Name属性的firstName属性值为"八戒"
		System.out.println(p.getName().getFirstName());
	}
}