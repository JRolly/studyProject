#include "stdafx.h"

////////////////////////////////////////////////////////////
//							ͨ�ð����ļ�
////////////////////////////////////////////////////////////
#ifndef __INCLUDE_DEF_H__
#define __INCLUDE_DEF_H__

#include "ToolsLib.h"

#define null	NULL

//ͨ�ð���
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#ifdef WIN32 //windows ���ض�����
	#include <stdio.h>
	#include <conio.h>
	#include <windows.h>
	#include <process.h>
	#include <winsock.h>
#else //Linux Unix ���ض�����
	#include <unistd.h>
	#include <errno.h>
	#include <pthread.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <string.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <termios.h>
	#include <netdb.h>
	#include <getopt.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif



#endif	// __INCLUDE_DEF_H__