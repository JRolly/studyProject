////////////////////////////////////////////////////////////
//							通用包含文件
////////////////////////////////////////////////////////////


#ifndef __INCLUDE_DEF_H__
#define __INCLUDE_DEF_H__

#define WIN32


#define null	NULL

//通用包含
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <signal.h>
#ifdef WIN32 //windows 下特定包含
	#include <conio.h>
	#include <windows.h>
	#include <process.h>
	#include <winsock.h>
#else //Linux Unix 下特定包含
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