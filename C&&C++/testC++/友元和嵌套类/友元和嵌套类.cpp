#include <iostream>
using namespace std;

//电视类和遥控器类

//TV类
class TV
{
public:
	friend class Tele;	//	将遥控器类设置为电视类的友元类，这样可以通过一些方法来设置封装在TV类中的各个属性及其属性值
	TV():on_off(off),volume(20),channel(3),mode(tv){}	//设置默认的出场设置
private:
	enum{on,off};		//电源
	enum{tv,av};		//模式
	enum{minve,maxve = 100};	//频道
	enum{mincl,maxcl = 60};		//音量
	bool on_off;	//电源开关
	int volume;	//音量
	int channel;	//模式
	int mode;	//模式
};

//Tele类
class Tele
{
public:
	void OnOff(TV &t){t.on_off = (t.on_off == t.on) ? t.off : t.on;}	//设置电源
	void SetMode(TV &t){t.mode = (t.mode == t.tv) ? t.av : t.av;}	//设置模式
	bool VolumeUp(TV &t);	//音量增
	bool VolumeDown(TV &t);	//音量减
	bool ChannelUp(TV &t);	//频道增
	bool ChannelDown(TV &t);//频道减
	void show(TV &t)const;	//显示信息
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
		cout << "电视现在" << (t.on_off == t.on ? "开启" : "关闭") << endl;
		cout << "声音大小为" << t.volume << endl;
		cout << "模式为" << t.mode << endl;
		cout << "频道" << t.channel << endl;
	}
	else
	{
		cout << "电视现在" << (t.on_off == t.on ? "开启" : "关闭") << endl;
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

	cout << "增大音量" << endl;
	t1.VolumeUp(t2);
	cout << "频道+1" << endl;
	t1.ChannelUp(t2);
	cout << "模式转换" << endl;
	t1.SetMode(t2);
	t1.show(t2);
}