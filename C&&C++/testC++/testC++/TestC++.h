#ifndef __TESTCPP_H__
#define __TESTCPP_H__

#include <map>
#include <string>
using namespace std;

typedef struct  
{
	int a;
	int b;
	map<int, string> mapEnum;
} ST_SIG;

typedef struct  
{
	int aa;
	int bb;
	ST_SIG* pSig;
} ST_MSG;

class CMsg
{
public:
	map<int, ST_MSG> m_mapMsg;

};


#endif