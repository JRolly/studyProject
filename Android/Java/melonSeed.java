// ��һ�ţ������ţ�ÿ��ʮ�ţ��Ӱ����������ó�1/4�Ե�
// ������100�ţ��ʣ����˶��ٿţ�
/*
    ѭ����10��
    �ܹ��Ե� = ÿ��ѭ���Ե� + û��ѭ����10�ź���ܹ�ʣ����ķ�֮һ
    
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



    







