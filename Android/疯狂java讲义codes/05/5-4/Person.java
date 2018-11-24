

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Person
{
	private String name;
	private int age;

	public Person()
	{
	}

	public Person(String name , int age)
	{
		this.name = name;
		this.age = age;
	}

	public void setName(String name)
	{
		//执行合理性校验，要求用户名必须在2～6位之间
		if (name.length() > 6 || name.length() < 2)
		{
			System.out.println("您设置的人名不符合要求");
			return;
		}
		else
		{
			this.name = name;
		}
	}
	public String getName()
	{
		 return this.name;
	}

	public void setAge(int age)
	{
		//执行合理性校验，要求用户年龄必须在0～100之间
		if (age > 100 || age < 0)
		{
			System.out.println("您设置的年龄不合法");
			return;
		}
		else
		{
			this.age = age;
		}
	}
	public int getAge()
	{
		 return this.age;
	}
}