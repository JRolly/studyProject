/*
    ��ȡһ�γ��������ʱ�䡣
    ԭ����ȡ����ʼ�ͽ�����ʱ�䲢���
*/

/*
    ��ȡʱ�䣺System.currentTimeMillis();
*/

abstract class GetTime
{
    public final void getTime()
    {
        long start = System.currentTimeMillis();
        
        runCode();
        
        long end = System.currentTimeMillis();
        
        System.out.println("���룺"+(end-start));
    }
    
    public abstract void runCode();
}

class SubTime extends GetTime
{
    public void runCode()
    {
        for (int i = 0; i <= 100000; i++)
        {
            if (100000 == i)
                System.out.println("over!");
        }
    }
}

class RunTime
{
    public static void main(String[] args)
    {
        SubTime gt = new SubTime();
        //GetTime gt = new GetTime();
        gt.getTime();
    }
}