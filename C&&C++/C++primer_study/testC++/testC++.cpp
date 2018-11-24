#include <iostream>
#include <string>
using namespace std;

#pragma pack(1)


#define sw16(x) \
	((WORD)(\
	(((WORD)(x)&(WORD)0x00ffU)<< 8) |\
	(((WORD)(x)&(WORD)0xff00U)>> 8)))

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

struct BYTEST
{
	BYTE abyte;
	BYTE bbyte;
	WORD word1;
	BYTE cbyte;
	DWORD dword;
	BYTE dbyte;
	WORD word;
};

struct BST
{
	BYTE abyte;
	BYTE bbyte;
	BYTE cbyte;
	BYTE dbyte;
	BYTE ebyte;
	BYTE fbyte;
	BYTE gbyte;
};

char* biglittleSwap(char *str, DWORD len)
{
	char tmp;
	DWORD offset = 0;
	while(len-offset)
	{
		if (len - offset >=4)
		{//大于4字节，做4字节交换
			//交换首尾
			tmp = str[offset];
			str[offset] = str[offset+3];
			str[offset+3] = tmp;
			//交换中间
			tmp = str[offset+1];
			str[offset+1] = str[offset+2];
			str[offset+2] = tmp;
			offset += 4;
		}
		else if (len-offset >= 2 && len-offset < 4)
		{//大于2字节，小于4字节，做2字节交换
			tmp = str[offset];
			str[offset] = str[offset+1];
			str[offset+1] = tmp;
			offset += 2;
		}
		else
		{//小于2字节，只有1字节，不做交换
			offset += 1;
		}
	}
	return str;
}

void main()
{
	BYTEST st;
	char ch[sizeof(st)] = {0};
	char str[100] = {0};
	memset(&st, 0, sizeof(st));
	//st.abyte = 0x11;
	//st.bbyte = 0x22;
	//st.word1 = 0x3344;
	//st.cbyte = 0x55;		
	//st.dword = 0x66778899;
	//st.dbyte = 0xAA;
	//st.word = 0xBBCC;
	//memcpy(ch, &st, sizeof(st));
	
	BST bst;
	memset(&bst, 0, sizeof(bst));
	bst.abyte = 0x11;
	bst.bbyte = 0x22;
	bst.cbyte = 0x33;
	bst.dbyte = 0x44;
	bst.ebyte = 0x55;
	bst.fbyte = 0x66;
	bst.gbyte = 0x77;
	memcpy(ch, &bst, sizeof(bst));
	biglittleSwap(ch, sizeof(bst));

	memset(&bst, 0, sizeof(bst));

	memcpy(&bst, ch, sizeof(bst));
	string strmsg;
	for(int i = 0; i < sizeof(ch); ++i)
	{
		sprintf(str, "%02X", ch[i]);
		strmsg += str;
	}
	cout <<strmsg<<endl;



	system("PAUSE");
}