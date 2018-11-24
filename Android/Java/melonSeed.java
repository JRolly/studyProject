// 吃一颗，剥两颗，每吃十颗，从剥的所有中拿出1/4吃掉
// 现在有100颗，问：吃了多少颗？
/*
    循环吃10颗
    总共吃的 = 每次循环吃的 + 没次循环吃10颗后的总共剩余的四分之一
    
    10 20 20/4=5 15 20-5=15
    16 17
    17 19
    18 21
*/

class melon
{
    public static void main(String[] args)
    {   int eat = totalEat(100);
        System.out.println("I have ate "+eat+" melon seeds\n");
    }

    public static int totalEat(int totalResidue)
    {
        int eat = 0;
        int residue = 0;
        int eatTotal = 0;
        
        while (residue < totalResidue)
        {
            eat++;
            residue+=2;
            eatTotal++;
            if (10 == eat)
            {                               
                eatTotal += residue/4; 
                residue -= (residue/4);
                eat = 0;
            }
        }
        return eatTotal;
    }
}



    







