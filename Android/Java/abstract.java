/*
抽象类
    abstract
    1、抽象方法一定定义在抽象类中
    2、抽象方法和抽象类都必须被abstract关键字修饰
    3、抽象类不可以用new创建
    4、抽象类中的抽象方法要被使用必须由子类复写其所有的抽象方法后建立子类对象调用，
        如果子类只覆盖了部分抽象方法，那么该子类还是一个抽象类
*/

abstract clsaa Student
{
    abstract void study();
}

class BaseStudent extends Student
{
    void study()
    {
        System.out.println("Base Study!\n");
    }
}

class AbstractDemo
{
    public static void main(String[] args)
    {
        System.out.println("Abstract!\n");
        
    }
}
