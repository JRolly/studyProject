#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;

//������ݵ��ļ�
//1.���� fstream ͷ�ļ�
//2.���� ofstream ����
//3.���������ļ�����
//4.�ö���ɿ���cout��ʹ�ö����������뵽�ļ�
//5.�ر����ļ�������

void file_write()
{
	//ofstream ocout;
	//ocout.open("filedemo.txt");
	ofstream ocout("filedemo.txt");	//�������ϲ�
	ocout << "hello world";
	ocout.close();
}


//��ȡ�ļ��е�����
//1.���� fstream ͷ�ļ�
//2.���� ifstream ����
//3.���������ļ�����
//4.�ö�����cin
//5.�ر����ļ�������

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

//�ɶ�ȡ���ַ�
void read_write()
{
	const int num = 255;
	char tmp1[num] = {0};
	char tmp2[num] = {0};
	ofstream fout("demo1.txt");	//������������һ���ļ�
	cout << "������";
	cin.getline(tmp1,num-1,0);	// ���û������ȡ�У��������ַ�
	int n = strlen(tmp1);
	tmp1[n-1] = '\0';
	fout << tmp1;	//д���ļ���
	fout.close();	//�رյ�һ���ļ�

	ifstream fin("demo1.txt");	//������һ���ļ�
	fin.getline(tmp2,num-1,0);	//�ӵ�һ���ļ���ȡ�У��������ַ�
	fout.open("demo2.txt");		//�������򿪵ڶ����ļ�
	fout << tmp2;
	cout << tmp2;
	fin.close(); //�رյ�һ���ļ�
	fout.close(); //�رյڶ����ļ�
}

//���ļ���open����
/***************************************************************
*	void open(const char *file, int mode)
*	mode:
*		ios::in	������
*		ios::out д����
*		ios::ate	(at end)���ļ�ʱָ��ָ���ļ�ĩβ�����������ļ��κεط�д����
*		ios::app	(append)��ʱ��������ݣ��ļ�ָ�����ļ�ĩβ��ֻ����ĩβд����
*		ios::trunc	(truncate)Ĭ�ϣ������ļ��Ѵ��ڣ�������ļ�����
*		ios::nocreate	���ļ������ڣ��򲻽����ļ������ش�ʧ����Ϣ
*		ios::noreplace	���ļ�ʱ�����ǣ����ļ������򷵻ش�ʧ����Ϣ
*		ios::binary		���ļ�Ϊ�����ƣ�����Ϊ�ı��ļ�
****************************************************************/
void _open()
{
	const int num = 255;
	char tmp[num] = {0};
	ofstream fout("open.txt");
	fout << "������ļ�\n";
	fout.close();

	fout.open("open.txt",ios::app);
	fout << "��ӵ��ļ�";
	fout.close();

	ifstream fin("open.txt");
	fin.getline(tmp,num-1,0);
	cout << tmp << endl;
	fin.close();
}


//����ļ��Ƿ��
//	��������	eof()	bad()	fail()	good()

void check_file_open()
{
	ofstream fout("cfo.txt");
	fout << "������ļ�\n";
	fout.close();

	ifstream fin("cfo.txt");
	if (fin.good())		//if (fin)
	{
		cout << "�ļ��򿪳ɹ����������ļ����ݣ�\n";
		char ch;
		while (!fin.eof())	//δ���ļ�ĩβʱ
		{
			ch = fin.get();
			cout << ch;
		}
	}
	fin.close();

	fout.open("cfo.txt", ios::app);
	if (fout.is_open())	//�жϷ�Ĭ�Ϸ�ʽ�´��ļ��Ƿ�ɹ�
	{
		fout << "�ٴ�������ļ�\n";
	}
	fout.close();
	fin.clear();	//�����ظ�����һ���ļ�ʱ����������־λ��0�����򽫶��������ݣ�����ʲô��������ʹ�ø÷��������޴��
	
	fin.open("cfo.txt");
	if (fin.is_open())
	{
		cout << "�ļ��򿪳ɹ����������ļ����ݣ�\n";
		char ch;
		while (fin.get(ch))	//δ���ļ�ĩβʱ
		{
			cout << ch;
		}
	}
	fin.close();

	fin.open("cfo1.txt");
	if (fin.fail())		//if (!fin)
	{
		cout << "�ļ���ʧ�ܣ�\n";
	}
	fin.close();
}

//�������ļ�
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
	fout.write((char*)&pe,sizeof(pe));	//jaysi д���ļ�
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
		cerr << "�ļ���ʧ�ܣ�" << endl;
	}
}

//�����д����ļ�
//��׼����Ҫ������ļ�
void cmd_file(int argc,char *argv[])
{
	if (argc == 1)
	{
		cerr << "�ó���" << argv[0] << "δ�����ļ���" << endl;
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
			cerr << "���ܴ��ļ�" << argv[file] << endl;
			fin.clear();
			continue;
		}
		count = 0;
		while (fin.get(ch))
		{
			count++;
		}
		cout << count << "�ַ���" << argv[file] << endl;
		totle += count;
		fin.clear();
		fin.close();
	}
	cout << "�����ļ��е��ַ��ϼ�" << totle << endl;
}

//ָ����ȡ�ļ��е�����
//	istream &seekg(pos_type position);	��ָ�붨λ�����ļ���ͷposition���ֽڴ�
//	istream &seekg(off_type offset, ios::seekdir origin);	��ָ�붨λ������ڶ�������ָ����λ��offset���ֽڴ�
//	�ڶ�������һ��Ϊ��
//			ios::beg	������ļ���ͷƫ��
//			ios::cur	����ڵ�ǰλ��ƫ��
//			ios::end	������ļ�βƫ��
void file_offset()
{
	ofstream fout("offset.txt");
	if (!fout)
	{
		cerr << "�����ļ�ʧ��" << endl; 
	}
	fout << "123456789abcdefghijklmnopqrstuvwxyz";
	fout.close();

	ifstream fin("offset.txt");
	if (fin.fail())
	{
		cerr << "�ļ���ʧ��" << endl;
	}
	//fin.seekg(9,ios::beg);	//������ļ�ͷƫ��
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

//������ݵ��ļ�ָ��λ��
//	ostream &seekp(pos_type position);
//	ostream &seekp(off_type offset, ios::seekdir origin)	

void file_offset1()
{
	ofstream fout("offset1.txt");
	if (!fout)
	{
		cerr << "�����ļ�ʧ��" << endl;
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
		cerr << "�ļ���ʧ��" << endl;
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
	while (cin.get() != '\n')	//���Ե�Enter��
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
	//���ļ�д������
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
		cout << "���������֣�";
		cin.get(pp.name,num);
		cin.ignore();
		cout << "���������䣺";
		cin >> pp.age;
		cout << "���������أ�";
		cin >> pp.weight;
		fout.write((char*)&pp,sizeof(pp));
		cout << "�Ƿ�������룿��(Y),��(N)";
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

	//��ʾ�ļ�����
	fstream InOut;
	cout << fixed;
	InOut.open(file,ios::in|ios::out|ios::binary);
	int count = 0;
	if (InOut.is_open())
	{
		InOut.seekp(0);
		cout << "��ǰ����Ϊ��" << file << endl;
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
			cerr << "��ȡ����" << file << endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cerr << file << "���ܴ��ļ�" << endl;
		exit(EXIT_FAILURE);
	}

	//�޸��ļ�����
	long int line;
	cout << "������Ҫ�޸ĵı�ţ�";
	cin >> line;	
	deleteline();
	if (line < 0 || line >= count)
	{
		cerr << "��Ч���" << endl;
		exit(EXIT_FAILURE);
	}
	streampos place = line*sizeof(pp);
	InOut.seekg(place);
	if (InOut.fail())
	{
		cerr << "���Բ�ѯʧ��" << endl;
		exit(EXIT_FAILURE);
	}
	InOut.read((char*)&pp,sizeof(pp));
	cout << "��ѡ��Ĳ���Ϊ:\n";
	cout << line << ":" << setw(num) <<	pp.name << ":" << setprecision(0) << setw(12)
		<< pp.age << setprecision(2) << setw(16) << pp.weight << endl;
	if (InOut.eof())
	{
		InOut.clear();
	}
	cout << "���������֣�";
	cin.get(pp.name,num);
	cout << "���������䣺";
	cin >> pp.age;
	cout << "���������أ�";
	cin >> pp.weight;
	InOut.seekp(place);
	InOut.write((char*)&pp,sizeof(pp)) << flush;	
	if (InOut.fail())
	{
		cerr << "����д��ʧ��" << endl;
		exit(EXIT_FAILURE);
	}

	//�ٴ���ʾ����
	count = 0;
	InOut.seekp(0);
	cout << "��ǰ����Ϊ��" << file << endl;
	while (InOut.read((char*)&pp,sizeof(pp)))
	{
		cout << count++ << ":" << setw(num) <<	pp.name << ":" << setprecision(0) << setw(12)
			<< pp.age << setprecision(2) << setw(16) << pp.weight << endl;
	}
	InOut.close();
	cout << "���" << endl;
}


//��ʱ�ļ�
// #include <cstdio>
// char *tmpnam(char *name);
//	����	TMP_MAX	 tmpnam()�����Ե��õĴ���
//			L_tmpnam	��ʱ�ļ������ַ���Ŀ
void tmp_file()
{
	cout << "tmpnam()���������ô�����" << TMP_MAX << "\n"
		<< "��ʱ�ļ������ַ���:" << L_tmpnam << endl;
	char pszName[L_tmpnam] = {'\0'};
	cout << "������ϵͳ�Զ�������ʮ����ʱ�ļ������֣�" << endl;
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