/*
    final :���κ���������
   1. ��final���ε��಻�ܱ��̳У�Ϊ�˱��ⱻ�̳У����ิд
   2. ��final���η��������ܱ���д
   3. ��final���εı���ֻ�ܸ�ֵһ�Σ��ȿ������γ�Ա�������ֿ������ξֲ�����
    
    
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