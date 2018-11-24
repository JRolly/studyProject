#include <iostream>
using namespace std;

//�������ң������

//TV��
class TV
{
public:
	friend class Tele;	//	��ң����������Ϊ���������Ԫ�࣬��������ͨ��һЩ���������÷�װ��TV���еĸ������Լ�������ֵ
	TV():on_off(off),volume(20),channel(3),mode(tv){}	//����Ĭ�ϵĳ�������
private:
	enum{on,off};		//��Դ
	enum{tv,av};		//ģʽ
	enum{minve,maxve = 100};	//Ƶ��
	enum{mincl,maxcl = 60};		//����
	bool on_off;	//��Դ����
	int volume;	//����
	int channel;	//ģʽ
	int mode;	//ģʽ
};

//Tele��
class Tele
{
public:
	void OnOff(TV &t){t.on_off = (t.on_off == t.on) ? t.off : t.on;}	//���õ�Դ
	void SetMode(TV &t){t.mode = (t.mode == t.tv) ? t.av : t.av;}	//����ģʽ
	bool VolumeUp(TV &t);	//������
	bool VolumeDown(TV &t);	//������
	bool ChannelUp(TV &t);	//Ƶ����
	bool ChannelDown(TV &t);//Ƶ����
	void show(TV &t)const;	//��ʾ��Ϣ
};

bool Tele::VolumeUp(TV &t)
{
	if (t.volume < t.maxve)
	{
		t.volume++;
		return true;
	}
	else
	{
		return false;
	}
}

bool Tele::VolumeDown(TV &t)
{
	if (t.volume > t.minve)
	{
		t.volume--;
		return true;
	}
	else
	{
		return false;
	}
}

bool Tele::ChannelUp(TV &t)
{
	if (t.channel < t.maxcl)
	{
		t.channel++;
		return true;
	}
	else
	{
		return false;
	}
}

bool Tele::ChannelDown(TV &t)
{
	if (t.channel > t.mincl)
	{
		t.channel--;
		return true;
	}
	else
	{
		return false;
	}
}

void Tele::show(TV &t)const
{
	if (t.on_off == t.on)
	{
		cout << "��������" << (t.on_off == t.on ? "����" : "�ر�") << endl;
		cout << "������СΪ" << t.volume << endl;
		cout << "ģʽΪ" << t.mode << endl;
		cout << "Ƶ��" << t.channel << endl;
	}
	else
	{
		cout << "��������" << (t.on_off == t.on ? "����" : "�ر�") << endl;
	}
}

//main
void main()
{
	Tele t1;
	TV t2;
	t1.show(t2);
	t1.OnOff(t2);
	t1.show(t2);

	cout << "��������" << endl;
	t1.VolumeUp(t2);
	cout << "Ƶ��+1" << endl;
	t1.ChannelUp(t2);
	cout << "ģʽת��" << endl;
	t1.SetMode(t2);
	t1.show(t2);
}