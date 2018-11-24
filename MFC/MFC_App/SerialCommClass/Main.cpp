#include "SerialComm.h"
#include <iostream>
using namespace  std;

void main()
{
	string sndbuf;
	string rcvbuf;
	HANDLE hCom;
	OVERLAPPED os_read;
	OVERLAPPED os_write;
	char str[SENDBUFFSIZE] = {0};
	SerialComm serCom;
	if (!serCom.init("COM3", 115200))
	{
		cout << "init error."<<endl;
		return;
	}
	cout <<"Input :";
	cin>>sndbuf;
	hCom = serCom.getCom();
	os_write = serCom.getOverlappedWrite();
	os_read = serCom.getOverlappedRead();
	strcpy(str, sndbuf.c_str());
	if (-1 == serCom.sendData(hCom, str, os_write))
	{
		cout << "Send Error."<<endl;
		system("PAUSE");
		return;
	}
	serCom.serOverlappedWrite(os_write);
	memset(str, 0, SENDBUFFSIZE);
	if (-1 == serCom.recvData(hCom, str, os_read))
	{
		cout << "Receive Error."<<endl;
		system("PAUSE");
		return;
	}
	rcvbuf = str;
	cout<<rcvbuf<<endl;

	system("PAUSE");
}