#include <iostream>
using namespace std;

void main()
{
	//char a[20] = "hello";
	//char *p = &a[0];

	//cout << "sizeof(a) " << sizeof(a) << endl;
	//cout << "strlen(a) " << strlen(a) << endl;
	//cout << "sizeof(p) " << sizeof(p) << endl;

	int count[256]={0};//ASCÂë×Ö·û£¬256¸ö
	char *p="0jjjjjsfasfjjjstuowerlllllfdsluuuuuuuu&0000000000*^#@+ljhfdsl",max=0;
	while (*p)
	{
		max=++count[*p]>count[max]?*p:max;
		p++;
	}
	cout<<"max times char is: "<<"="<<count[max]<<endl;
	system("PAUSE");

}