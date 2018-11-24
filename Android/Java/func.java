/**
函数

   修饰符 返回类型 函数名(参数列表)
   {
        ...
        return 返回值;
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
    
    //完成一个运算
    public static int getResult(int num)
    {
        return num * 2 + 4;
    }
}