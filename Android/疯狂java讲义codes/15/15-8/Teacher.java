

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Teacher 
	implements java.io.Serializable
{
	private String name;
	private Person student;

	public Teacher(String name , Person student)
	{
		this.name = name;
		this.student = student;
	}

	public void setName(String name)
	{
		this.name = name;
	}
	public String getName()
	{
		 return this.name;
	}

	public void setStudent(Person student)
	{
		this.student = student;
	}
	public Person getStudent()
	{
		 return this.student;
	}

}