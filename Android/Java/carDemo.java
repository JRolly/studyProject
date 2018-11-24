/**
    类与对象的关系
*/

class Car
{
    String color = "红色";
    int num = 4;
    
    void run()
    {
        System.out.println(color+".."+num);
    }
}

class CarDemo
{
    public void main(String[] args)
    {
        Car c = new Car();  //c就是一个类 类型的变量,执行对象
        c.color = "Blue";   //改变对象属性
        c.run();
        
        //匿名对象
        //调用方法有意义，调用属性是没有意义的
        //对一个对象进行多个成员调用时不可使用匿名对象
        //匿名对象可以做为实际参数传递使用
       // new Car().num = 5;
       // new Car().color = "green";
       // new Car().run();
       
       Car ca = new Car();
       show(ca);
       // show(new Car()); //匿名对象的使用
    }
    
    public static void show(Car c)
    {
        c.num = 3;
        c.color = "black";
        c.run();
    }
}