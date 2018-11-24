using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class MyClass
{
    public void ListInts(params int[] inVals)
    {
        if ((inVals != null) && (inVals.Length != 0))
        {
            for (int i = 0; i < inVals.Length; ++i)
            {
                inVals[i] = inVals[i] * 10;
                Console.WriteLine("{0}", inVals[i]);
            }    
        }
    }
}


class Proi
{
    private int intVal;
    public int IntVal
    {
        get { return intVal; }
        set { intVal = value; }
    }

    public int AutoVal
    {
        get;
        set;
    }

    public static int StaticVal
    {
        set;
        get;
    }
}


namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
//             int a = 1, b = 2, c = 3;
//             int[] arr = {1, 2, 3};
//             MyClass mc = new MyClass();
//             mc.ListInts(a, b, c);
//             foreach (int x in arr)
//                 Console.WriteLine("{0}", x);
// 
//             mc.ListInts(arr);
//             foreach (int x in arr)
//                 Console.WriteLine("{0}", x);


            Proi proi = new Proi();
            proi.IntVal = 1;
            proi.AutoVal = 10;
            Proi.StaticVal = 100;
            Console.WriteLine("{0}, {1}, {2}", proi.IntVal, proi.AutoVal, Proi.StaticVal);

            
            Console.Read();
        }
    }
}
