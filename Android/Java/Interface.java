/*
    �ӿ�,interface
    ���������еķ������ǳ��󷽷�����ô�������ͨ����ڵķ�ʽ����ʾ
    class���ڶ�����
    interface��������ӿ�
    
    �ӿڶ���ʱ����ʽ�ص㣺
    1.�ӿ��г������壺����������
    ������public static final
    ������public abstract
   �ӿ��еĳ�Ա����public��
   
   �ӿ��ǲ����Դ�������ģ���Ϊ�г��󷽷�����Ҫ������ʵ��
*/

/*
    �ӿڿ��Ա����ʵ��
    �ӿ�֮��֧�ֶ�̳�
*/

interface Inter
{
    public static final int NUM = 3;
    public abstract void show();
}

interface InterA
{
    public abstract void method();
}

class Test implements Inter,InterA
{
    public void show(){}
    public void method(){}
}

interface A
{
    void method();
}

interface B extends B
{
    void method();
}


class InterfaceDemo
{
    public static void main(String[] args)
    {
        Test t = new Test();
        System.out.println("Interface!\n");
        System.out.println(t.NUM);
        System.out.println(Test.NUM);
        System.out.println(Inter.NUM);
    }
}