#include <iostream>
#include <string>

using namespace std;


class Screen
{
public:
	typedef string::size_type index;

	char get() const { return contents[cursor];}
	char get(index r, index c) const;
	inline index get_cursor() const;
	Screen(index hght, index wdth, const string &cntnts = "");

	Screen& move(index r, index c);
	Screen& set(char c);
	Screen& display(ostream &os);
	const Screen& display(ostream &os) const;

private:
	string contents;
	index cursor;	
	index height, width;
	void do_display(ostream &os) const;
};

Screen::Screen(index hght, index wdth, const string &cntnts /*= ""*/):
		cursor(0), height(hght), width(wdth)
{
	//将整个屏幕内容置为空
	contents.assign(hght*wdth, ' ');
	//用形参string对象个的内容设置屏幕对应字符
	if (cntnts.size() != 0)
		contents.replace(0, cntnts.size(), cntnts);
}

char Screen::get(index r, index c) const
{
	index row = r * width;
	return contents[row + c];
}

inline Screen::index Screen::get_cursor() const
{
	return cursor;
}

Screen& Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

Screen& Screen::move(index r, index c)
{
	if (r >= width || c >= width)
	{
		cerr<<"invalid row or column"<<endl;
		throw EXIT_FAILURE;
	}

	index row = r * width;
	cursor = row + c;
	return *this;
}

void Screen::do_display(ostream &os) const
{
	string::size_type index = 0;
	while (index != contents.size())
	{
		os<<contents[index];
		if ((index+1) % width == 0)
		{
			os<<"\n";
		}
		index++;
	}
}

Screen& Screen::display(ostream &os)
{
	do_display(os);
	return *this;
}

const Screen& Screen::display(ostream &os) const
{
	do_display(os);
	return *this;
}

//
//void main()
//{
//	cout<<"测试Screen类"<<endl;
//	Screen myScreen(5, 6, "aaaaa\naaaaa\naaaaa\naaaaa\naaaaa\n");
//	//Screen myScreen(5, 6);
//	myScreen.move(4, 0).set('#').move(0, 3).set('@').display(cout);
//	//myScreen.move(3, 3).set('@').display(cout);
//
//	system("PAUSE");
//}