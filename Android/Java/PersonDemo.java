/**
    ��װ
    private: ˽�У�Ȩ�����η���ֻ�ڱ�������Ч
    
    ��age˽�л��Ժ����⼴ʹ�����˶���Ҳ����ֱ�ӷ��ʣ�
    ��Ҫ��Person������on����Ӧ����age�ķ���
*/

class Person
{
    private int age;    
    void speak()
    {
        System.out.println("age:"+age);
    }
    public void setAge(int a)
    {
        if (age > 0 && age < 130)
            age = a;
        else
            System.out.println("�Ƿ�age");
    }
    public int getAge()
    {
        return age;
    }
}

class PersonDemo
{
    public static void main(String[] args)
    {
        Person p = new Person();
        // p.age = 20;
        p.setAge(20);
        p.speak();
    }
}