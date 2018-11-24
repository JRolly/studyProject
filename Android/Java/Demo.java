/**
作者：Jaysi
*/

class Demo
{
    public static void main(String[] args)
    {
        int x = 4;
        System.out.println(x);
        byte b = 2; // -128 ~ 127
        System.out.println(b);
        short s = 30000;
        System.out.println(s);
        long l = 4l;
        System.out.println(l);
        float f = 2.3f;
        System.out.println(f);
        double d = 33.3;
        System.out.println(d);
        char ch = 'c';
        System.out.println(ch);
        boolean bl = true;
        System.out.println(bl);
        
        //ch = ch + 1;
        System.out.println((char)('a'+1));
        
        System.out.println("Hello java");
    }
}

//十进制转十六进制
class opera
{
    public static void main(String[] args)
    {
        int num = 60;
        int n1 = num & 15;
        
        int tmp = 60 >> 4;
        int n2 = tmp & 15;
        System.out.println(n2);
        System.out.println((char)(n1-10+'A'));
    }
}