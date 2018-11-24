

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
 
//定义一个Person类
class Person
{
	private String name;
	private String idStr;
	public Person(){}
	public Person(String name , String idStr)
	{
		this.name = name;
		this.idStr = idStr;
	}
	//下面是name和idStr的setter和getter方法。
	public void setName(String name)
	{
		this.name = name;
	}
	public String getName()
	{
		 return this.name;
	}

	public void setIdStr(String idStr)
	{
		this.idStr = idStr;
	}
	public String getIdStr()
	{
		 return this.idStr;
	}
//	//重写equals方法，提供自定义的相等标准
//	public boolean equals(Object obj)
//	{
//		//只有当obj是Person对象
//		if (obj != null && obj instanceof Person)
//		{
//			Person personObj = (Person)obj;
//			//并且当前对象的idStr与obj对象的idStr相等才可判断两个对象相等
//			if (this.getIdStr().equals(personObj.getIdStr()))
//			{
//				return true;
//			}
//		}
//		return false;
//	}

	//重写equals方法，提供自定义的相等标准
	public boolean equals(Object obj)
	{
		//待比较的两个对象是同一个对象，直接返回true
		if(this == obj)
		{
			return true;
		}
		//只有当obj是Person对象
		if (obj != null && obj.getClass() == Person.class)
		{
			Person personObj = (Person)obj;
			//并且当前对象的idStr与obj对象的idStr相等才可判断两个对象相等
			if (this.getIdStr().equals(personObj.getIdStr()))
			{
				return true;
			}
		}
		return false;
	}

}
public class OverrideEqualsRight
{
	public static void main(String[] args) 
	{
		Person p1 = new Person("孙悟空" , "12343433433");
		Person p2 = new Person("孙行者" , "12343433433");
		Person p3 = new Person("孙悟饭" , "99933433");
		//p1和p2的idStr相等，所以输出true
		System.out.println("p1和p2是否相等？" + p1.equals(p2));
		//p2和p3的idStr不相等，所以输出false
		System.out.println("p2和p3是否相等？" + p2.equals(p3));
	}
}