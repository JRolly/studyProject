/**
����

   ���η� �������� ������(�����б�)
   {
        ...
        return ����ֵ;
   }
*/

class FunctionDemo
{
    public static void main(String[] args)
    {
        int num = 2;
        num = getResult(num);
        System.out.println(num);
    }
    
    //���һ������
    public static int getResult(int num)
    {
        return num * 2 + 4;
    }
}