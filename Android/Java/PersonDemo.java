/**
    封装
    private: 私有，权限修饰符，只在本类中有效
    
    将age私有化以后，类外即使建立了对象也不能直接访问，
    需要在Person类中体on个对应访问age的方法
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
            System.out.println("非法age");
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