/*
������
    abstract
    1�����󷽷�һ�������ڳ�������
    2�����󷽷��ͳ����඼���뱻abstract�ؼ�������
    3�������಻������new����
    4���������еĳ��󷽷�Ҫ��ʹ�ñ��������ิд�����еĳ��󷽷��������������ã�
        �������ֻ�����˲��ֳ��󷽷�����ô�����໹��һ��������
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
