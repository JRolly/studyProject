/**
    数组
    元素类型[] 数组名 = nwe 元素类型[元素个数或数组长度]
    元素类型 数组名[] = nwe 元素类型[元素个数或数组长度]
    元素类型[] 数组名 = nwe 元素类型[]{}
    arr = NULL;
    
    数组名.length //获取数组长度
*/
class ArrayDemo
{
    public static void main(String[] args)
    {
        int[] arr = new int[3];
        int[] arr1 = new int[]{1,2,3,4,5};
        
        int arrlen = arr.length;    //数组长度 
        System.out.println(arr[0]);
       
        //printArray(arr1);
        int max = getMax(arr1);
        System.out.println("最大值是"+max);
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
    
    //返回数组中最大值
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