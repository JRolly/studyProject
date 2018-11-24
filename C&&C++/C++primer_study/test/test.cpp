#include <iostream>

using namespace std;

struct Base
{
	void foo(int);
protected:
	int bar;
	double foo_bar;
};

struct Derivid : public Base
{
	void foo(string);
	bool fbar(Base *bp);
	void foobar();
protected:
	string bar;
};

//bool Derivid::fbar(Base *bp)
//{
//	return foo_bar == bp->foo_bar;
//}

char* strcopy(char *dest, const char *src)
{
	while((*dest++ = *src++) != '\0');
	return dest;
}

typedef unsigned char BYTE;
typedef unsigned short WORD;

struct BYTEST
{
	BYTE abyte;
	BYTE bbyte;
	BYTE cbyte;
	BYTE dbyte;
	WORD word;
};



void main()
{
	float f = 12.234f;
	float *pf = &f;
	cout << *pf <<endl;


	system("PAUSE");
}

