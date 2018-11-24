#include <stdio.h>

long long totalEat(int totalResidue);

void main(int argc, char *argv[])
{
	long long eatTotal = totalEat(79);
	printf("I have ate %d melon seeds\n",eatTotal);
}




long long totalEat(int totalResidue)
{
	int eat = 0;
	int residue = 0;
	long long eatTotal = 0;

	while (residue < totalResidue)
	{
		eat++;
		residue+=2;
		eatTotal++;
		if (10 == eat)
		{                               
			eatTotal += residue>>2; 
			residue -= (residue>>2);
			eat = 0;
			printf("residut = %d\n",residue);
		}
	}
	return eatTotal;
}