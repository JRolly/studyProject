/*
    接口,interface
    当抽象类中的方法都是抽象方法，那么该类可以通过借口的方式来表示
    class用于定义类
    interface用来定义接口
    
    接口定义时，格式特点：
    1.接口中常见定义：常量，方法
    常量：public static final
    方法：public abstract
   接口中的成员都是public的
   
   接口是不可以创建对象的，因为有抽象方法，需要被子类实现
*/

/*
    接口可以被类多实现
    接口之间支持多继承
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