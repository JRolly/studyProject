/*
    Polymorphism,多态
    
    1.多态的体现
        父类的引用指向了自己的子类对象   
        父类的引用也可以接收自己的子类对象
    2.多态的前提
        必须是类与类之间有关系，要么继承，要么实现
        通常，存在覆盖
    3.多态的好处
        提高程序的扩展性，
        弊端：只能使用父类的引用访问父类中的成员
    4.多态的应用
    
    5.注意事项

*/

abstract class Animal
{
    abstract void eat();
}

class Cat extends Animal
{
    public void eat()
    {
        System.out.println("吃鱼");
    }
    public void catchMouse()
    {
        System.out.println("抓老鼠");
    }
}

class Dog extends Animal
{
    public void eat()
    {
        System.out.println("吃骨头");
    }
    public void eatBone()
    {
        System.out.println("啃骨头");
    }
}

class Pig extends Animal
{
    public void eat()
    {
        System.out.println("吃饲料");
    }
    public void sleep()
    {
        System.out.println("Pig睡觉");
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
        
        //强制将父类的引用，转换成子类类型
        // Animal a = new Cat();   //类型提升
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