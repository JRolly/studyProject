/**
    ����
    Ԫ������[] ������ = nwe Ԫ������[Ԫ�ظ��������鳤��]
    Ԫ������ ������[] = nwe Ԫ������[Ԫ�ظ��������鳤��]
    Ԫ������[] ������ = nwe Ԫ������[]{}
    arr = NULL;
    
    ������.length //��ȡ���鳤��
*/
class ArrayDemo
{
    public static void main(String[] args)
    {
        int[] arr = new int[3];
        int[] arr1 = new int[]{1,2,3,4,5};
        
        int arrlen = arr.length;    //���鳤�� 
        System.out.println(arr[0]);
       
        //printArray(arr1);
        int max = getMax(arr1);
        System.out.println("���ֵ��"+max);
    }
    
    public static void printArray(int[] arr)
    {
        for (int x = 0; x < arr.length; x++)
        {
            if (x != arr.length-1)
                System.out.print(arr[x]+",");
            else
                System.out.print(arr[x]);
        }
        
    }
    
    //�������������ֵ
    public static int getMax(int[] arr)
    {
        int max = arr[0];
        for (int i = 2; i < arr.length; i++)
        {
            if (arr[i] > max)
                max = arr[i];
        }
        return max;
    }
}