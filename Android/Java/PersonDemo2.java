/*
    ���캯��
	����һ�����ͻ���ö�Ӧ�Ĺ��캯��
	�������ڸ�������г�ʼ��
    
	��һ������û�ж��幹�캯��ʱ����ôϵͳ��������һ���ղ����Ĺ��캯��
	
	���������Ǹ����ж������ͳһ��ʼ��
*/

class Person
{
	private int age;
	private String name;
    Person()
    {
        System.out.println("���캯��");
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