/**
    �������Ĺ�ϵ
*/

class Car
{
    String color = "��ɫ";
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
        Car c = new Car();  //c����һ���� ���͵ı���,ִ�ж���
        c.color = "Blue";   //�ı��������
        c.run();
        
        //��������
        //���÷��������壬����������û�������
        //��һ��������ж����Ա����ʱ����ʹ����������
        //�������������Ϊʵ�ʲ�������ʹ��
       // new Car().num = 5;
       // new Car().color = "green";
       // new Car().run();
       
       Car ca = new Car();
       show(ca);
       // show(new Car()); //���������ʹ��
    }
    
    public static void show(Car c)
    {
        c.num = 3;
        c.color = "black";
        c.run();
    }
}