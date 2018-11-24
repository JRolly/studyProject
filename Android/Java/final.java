/*
    final :修饰函数、变量
   1. 被final修饰的类不能被继承，为了避免被继承，子类复写
   2. 被final修饰发方法不能被复写
   3. 被final修饰的变量只能赋值一次，既可以修饰成员变量，又可以修饰局部变量
    
    
*/

class Demo
{
    final int x = 3;   
    public static final double PI = 3.14;
    //final void show1(){}
    void show2(){}
}

class SubDemo extends Demo
{
    void show1(){}
}

class FinalDemo
{
    public static void main(String[] args)
    {
        System.out.println("Final!");
    }
}