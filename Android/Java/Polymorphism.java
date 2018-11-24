/*
    Polymorphism,��̬
    
    1.��̬������
        ���������ָ�����Լ����������   
        ���������Ҳ���Խ����Լ����������
    2.��̬��ǰ��
        ������������֮���й�ϵ��Ҫô�̳У�Ҫôʵ��
        ͨ�������ڸ���
    3.��̬�ĺô�
        ��߳������չ�ԣ�
        �׶ˣ�ֻ��ʹ�ø�������÷��ʸ����еĳ�Ա
    4.��̬��Ӧ��
    
    5.ע������

*/

abstract class Animal
{
    abstract void eat();
}

class Cat extends Animal
{
    public void eat()
    {
        System.out.println("����");
    }
    public void catchMouse()
    {
        System.out.println("ץ����");
    }
}

class Dog extends Animal
{
    public void eat()
    {
        System.out.println("�Թ�ͷ");
    }
    public void eatBone()
    {
        System.out.println("�й�ͷ");
    }
}

class Pig extends Animal
{
    public void eat()
    {
        System.out.println("������");
    }
    public void sleep()
    {
        System.out.println("Pig˯��");
    }
}



class Polymorphism
{
    public static void main(String[] args)
    {
        // Cat c = new Cat();
        // func(c);
        
        func(new Cat());
        func(new Dog());
        
        //ǿ�ƽ���������ã�ת������������
        // Animal a = new Cat();   //��������
        // Cat c = (Cat)a;
        // c.catchMouse();
        
    }
    
    public static void func(Animal a)
    {
        a.eat();
        if (a instanceof Cat)
        {
            Cat c = (Cat)a;
            c.catchMouse();
        }
        else if (a instanceof Dog)
        {
            Dog c = (Dog)a;
            c.eatBone();
        }
    }
    // public static void func(Cat c)
    // {
        // c.eat();
    // }
    
}