/**
	static	�������γ�Ա
	����Ա����̬���κ󣬾Ͷ���һ�ֵ��÷�ʽ�����˱�������ã�������ֱ�ӱ��������ã�
		����.��̬��̬��Ա
	
	�ص㣺
		������ļ��ض�����
		�����ڶ������
		�����ж���������
		����ֱ�ӱ���������
	
	ע�����
	��̬����ֻ�ܷ��ʾ�̬��Ա
	��̬�����в����Զ���this,super�ؼ���
	
	�ô����Զ���Ĺ������ݽ��е����ռ�Ĵ洢����ʡ�ռ䣬
		  ����ֱ�ӱ���������
	��������������̫��
		  ���ʳ��־�����
		  
	Ӧ�ã�
		ÿһ��Ӧ�ó����й��ԵĹ��ܣ����Խ���Щ���ܷ�װ���Ա㸴��
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