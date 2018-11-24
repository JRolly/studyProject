#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;

//输出数据到文件
//1.包含 fstream 头文件
//2.建立 ofstream 对象
//3.将对象与文件关联
//4.该对象可看作cout，使用对象将数据输入到文件
//5.关闭与文件的连接

void file_write()
{
	//ofstream ocout;
	//ocout.open("filedemo.txt");
	ofstream ocout("filedemo.txt");	//将两部合并
	ocout << "hello world";
	ocout.close();
}


//读取文件中的数据
//1.包含 fstream 头文件
//2.建立 ifstream 对象
//3.将对象与文件关联
//4.该对象看作cin
//5.关闭与文件的连接

void file_read()
{
	char tmp[20] = {0};
	ifstream fin("filedemo.txt");
	ofstream fout("filedemo1.txt");
	fin >> tmp;
	fout << tmp << endl;
	cout << tmp << endl;
	fin.close();
	fout.close();
}

//可读取空字符
void read_write()
{
	const int num = 255;
	char tmp1[num] = {0};
	char tmp2[num] = {0};
	ofstream fout("demo1.txt");	//创建并关联第一个文件
	cout << "请输入";
	cin.getline(tmp1,num-1,0);	// 从用户输入读取行，包括空字符
	int n = strlen(tmp1);
	tmp1[n-1] = '\0';
	fout << tmp1;	//写入文件中
	fout.close();	//关闭第一个文件

	ifstream fin("demo1.txt");	//关联第一个文件
	fin.getline(tmp2,num-1,0);	//从第一个文件读取行，包括空字符
	fout.open("demo2.txt");		//创建并打开第二个文件
	fout << tmp2;
	cout << tmp2;
	fin.close(); //关闭第一个文件
	fout.close(); //关闭第二个文件
}

//打开文件的open函数
/***************************************************************
*	void open(const char *file, int mode)
*	mode:
*		ios::in	读操作
*		ios::out 写操作
*		ios::ate	(at end)打开文件时指针指向文件末尾，但可以在文件任何地方写数据
*		ios::app	(append)打开时不清空数据，文件指针在文件末尾，只能在末尾写数据
*		ios::trunc	(truncate)默认，若打开文件已存在，则清空文件内容
*		ios::nocreate	打开文件不存在，则不建立文件，返回打开失败信息
*		ios::noreplace	打开文件时不覆盖，若文件存在则返回打开失败信息
*		ios::binary		打开文件为二进制，否则为文本文件
****************************************************************/
void _open()
{
	const int num = 255;
	char tmp[num] = {0};
	ofstream fout("open.txt");
	fout << "输出到文件\n";
	fout.close();

	fout.open("open.txt",ios::app);
	fout << "添加到文件";
	fout.close();

	ifstream fin("open.txt");
	fin.getline(tmp,num-1,0);
	cout << tmp << endl;
	fin.close();
}


//检查文件是否打开
//	布尔函数	eof()	bad()	fail()	good()

void check_file_open()
{
	ofstream fout("cfo.txt");
	fout << "输出到文件\n";
	fout.close();

	ifstream fin("cfo.txt");
	if (fin.good())		//if (fin)
	{
		cout << "文件打开成功，以下是文件内容：\n";
		char ch;
		while (!fin.eof())	//未到文件末尾时
		{
			ch = fin.get();
			cout << ch;
		}
	}
	fin.close();

	fout.open("cfo.txt", ios::app);
	if (fout.is_open())	//判断非默认方式下打开文件是否成功
	{
		fout << "再次输出到文件\n";
	}
	fout.close();
	fin.clear();	//用于重复读入一个文件时，将各个标志位清0，否则将读不到数据，无论什么编译器，使用该方法都是无错的
	
	fin.open("cfo.txt");
	if (fin.is_open())
	{
		cout << "文件打开成功，以下是文件内容：\n";
		char ch;
		while (fin.get(ch))	//未到文件末尾时
		{
			cout << ch;
		}
	}
	fin.close();

	fin.open("cfo1.txt");
	if (fin.fail())		//if (!fin)
	{
		cout << "文件打开失败！\n";
	}
	fin.close();
}

//二进制文件
const int num = 20;
struct people
{
	char name[num];
	double weigth;
	int tall;
	int age;
	char sex;
};
void file_binary()
{
	people pe = {"Jaysi",56.5,170,22,'f'};
	ofstream fout("people.txt",ios::binary);
	fout.write((char*)&pe,sizeof(pe));	//jaysi 写入文件
	fout.close();

	people pe1 = {"Rolly",49.5,158,22,'m'};
	ifstream fin("people.txt",ios::binary);
	fin.read((char*)&pe1,sizeof(pe1));
	cout << pe1.name << " " << pe1.age << " " << pe1.sex << " "
		 << pe1.tall << " " << pe1.weigth << " " <<endl;
	fin.close();

	fout.open("people.txt",ios::app|ios::binary);
	fout.write((char*)&pe1,sizeof(pe1));
	fout.close();

	people petmp;
	fin.open("people.txt",ios::in|ios::binary);
	if (fin.good())
	{
		while (!fin.eof())
		{
			fin.read((char*)&petmp,sizeof(petmp));
			cout << petmp.name << " " << petmp.age << " " << petmp.sex << " "
				<< petmp.tall << " " << petmp.weigth << " " <<endl;
		}
		fin.close();
	}
	else
	{
		cerr << "文件打开失败！" << endl;
	}
}

//命令行处理文件
//先准备需要处理的文件
void cmd_file(int argc,char *argv[])
{
	if (argc == 1)
	{
		cerr << "该程序" << argv[0] << "未操作文件名" << endl;
		exit(EXIT_FAILURE);
	}
	ifstream fin;
	long count;
	long totle = 0;
	char ch;
	for (int file = 1; file < argc; file++)
	{
		fin.open(argv[file]);
		if (!fin.is_open())
		{
			cerr << "不能打开文件" << argv[file] << endl;
			fin.clear();
			continue;
		}
		count = 0;
		while (fin.get(ch))
		{
			count++;
		}
		cout << count << "字符在" << argv[file] << endl;
		totle += count;
		fin.clear();
		fin.close();
	}
	cout << "所有文件中的字符合计" << totle << endl;
}

//指定读取文件中的数据
//	istream &seekg(pos_type position);	将指针定位到离文件开头position个字节处
//	istream &seekg(off_type offset, ios::seekdir origin);	将指针定位到距离第二个参数指定的位置offset个字节处
//	第二个参数一般为：
//			ios::beg	相对于文件开头偏移
//			ios::cur	相对于当前位置偏移
//			ios::end	相对于文件尾偏移
void file_offset()
{
	ofstream fout("offset.txt");
	if (!fout)
	{
		cerr << "创建文件失败" << endl; 
	}
	fout << "123456789abcdefghijklmnopqrstuvwxyz";
	fout.close();

	ifstream fin("offset.txt");
	if (fin.fail())
	{
		cerr << "文件打开失败" << endl;
	}
	//fin.seekg(9,ios::beg);	//相对于文件头偏移
	//fin.seekg(9);
	fin.seekg(-2,ios::end);
	char ch;
	while (fin.get(ch))
	{
		cout << ch;
	}
	cout << endl;
	fin.close();
}

//输出数据到文件指定位置
//	ostream &seekp(pos_type position);
//	ostream &seekp(off_type offset, ios::seekdir origin)	

void file_offset1()
{
	ofstream fout("offset1.txt");
	if (!fout)
	{
		cerr << "创建文件失败" << endl;
	}
	fout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	fout.close();

	fstream fout1;
	fout1.open("offset1.txt");
	char ch[] = "123456789abcdefghijklmnopqrstuvwxyz";
	fout1.seekp(9,ios::beg);
	fout1 << ch;
	fout1.close();

	ifstream fin("offset1.txt");
	if (fin.fail())
	{
		cerr << "文件打开失败" << endl;
	}
	char ch1;
	while (fin.get(ch1))
	{
		cout << ch1;
	}
	cout << endl;
	fin.close();
}

//file seek
void deleteline()
{
	while (cin.get() != '\n')	//忽略掉Enter键
		continue;
}
struct people1
{
	char name[num];
	int age;
	float weight;
};
void file_seek()
{
	//向文件写入内容
	const char *file = "fileseek.txt";
	//people1 pp = {"JayR",22,45.9};
	ofstream fout(file,ios::out|ios::binary);
	//fout.write((char*)&pp,sizeof(pp));
	//fout.close();

	//people1 pp1 = {"RollyJ",23,50.6};
	//fout.open(file,ios::in|ios::out|ios::binary);
	//fout.seekp(sizeof(pp),ios::beg);
	//fout.write((char*)&pp1,sizeof(pp1));
	//fout.close();
	people1 pp = {0};
	bool quit = true;
	while (quit)
	{
		cout << "请输入名字：";
		cin.get(pp.name,num);
		cin.ignore();
		cout << "请输入年龄：";
		cin >> pp.age;
		cout << "请输入体重：";
		cin >> pp.weight;
		fout.write((char*)&pp,sizeof(pp));
		cout << "是否继续输入？是(Y),否(N)";
		char choice;
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			deleteline();
			continue;
		}
		else
		{
			quit = false;
		}
	}
	fout.close();

	//显示文件内容
	fstream InOut;
	cout << fixed;
	InOut.open(file,ios::in|ios::out|ios::binary);
	int count = 0;
	if (InOut.is_open())
	{
		InOut.seekp(0);
		cout << "当前内容为：" << file << endl;
		while (InOut.read((char*)&pp,sizeof(pp)))
		{
			cout << count++ << ":" << setw(num) <<	pp.name << ":" << setprecision(0) << setw(12)
				<< pp.age << setprecision(2) << setw(16) << pp.weight << endl;
		}
		if (InOut.eof())
		{
			InOut.clear();
		}
		else
		{
			cerr << "读取错误" << file << endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cerr << file << "不能打开文件" << endl;
		exit(EXIT_FAILURE);
	}

	//修改文件内容
	long int line;
	cout << "请输入要修改的编号：";
	cin >> line;	
	deleteline();
	if (line < 0 || line >= count)
	{
		cerr << "无效编号" << endl;
		exit(EXIT_FAILURE);
	}
	streampos place = line*sizeof(pp);
	InOut.seekg(place);
	if (InOut.fail())
	{
		cerr << "尝试查询失败" << endl;
		exit(EXIT_FAILURE);
	}
	InOut.read((char*)&pp,sizeof(pp));
	cout << "你选择的操作为:\n";
	cout << line << ":" << setw(num) <<	pp.name << ":" << setprecision(0) << setw(12)
		<< pp.age << setprecision(2) << setw(16) << pp.weight << endl;
	if (InOut.eof())
	{
		InOut.clear();
	}
	cout << "请输入名字：";
	cin.get(pp.name,num);
	cout << "请输入年龄：";
	cin >> pp.age;
	cout << "请输入体重：";
	cin >> pp.weight;
	InOut.seekp(place);
	InOut.write((char*)&pp,sizeof(pp)) << flush;	
	if (InOut.fail())
	{
		cerr << "尝试写入失败" << endl;
		exit(EXIT_FAILURE);
	}

	//再次显示内容
	count = 0;
	InOut.seekp(0);
	cout << "当前内容为：" << file << endl;
	while (InOut.read((char*)&pp,sizeof(pp)))
	{
		cout << count++ << ":" << setw(num) <<	pp.name << ":" << setprecision(0) << setw(12)
			<< pp.age << setprecision(2) << setw(16) << pp.weight << endl;
	}
	InOut.close();
	cout << "完成" << endl;
}


//临时文件
// #include <cstdio>
// char *tmpnam(char *name);
//	常量	TMP_MAX	 tmpnam()最多可以调用的次数
//			L_tmpnam	临时文件名的字符数目
void tmp_file()
{
	cout << "tmpnam()函数最多调用次数：" << TMP_MAX << "\n"
		<< "临时文件名的字符数:" << L_tmpnam << endl;
	char pszName[L_tmpnam] = {'\0'};
	cout << "下面是系统自动创建的十个临时文件的名字：" << endl;
	for (int i = 0; i < 10; i++)
	{
		tmpnam(pszName);
		cout << pszName << endl;
	}
}


void main(int argc,char *argv[])
{
	//file_write();
	//file_read();
	//read_write();
	//_open();
	//check_file_open();
	//file_binary();
	//cmd_file(argc,&*argv);
	//file_offset();
	//file_offset1();
	//file_seek();
	tmp_file();
}