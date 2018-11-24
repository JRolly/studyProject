#include <iostream>
#include <string>

using namespace std;


class HasPtr
{
public:
	HasPtr(){}
	HasPtr(const int &p, int i = 0)
		:ptr(new int(p)), val(i){}

	HasPtr(const HasPtr &orig)
		:ptr(new int (*orig.ptr)), val(orig.val){}

	HasPtr& operator=(const HasPtr&);

	~HasPtr(){ delete ptr; ptr = NULL;}

	friend ostream& operator<<(ostream &os, const HasPtr &s);
	friend istream& operator>>(istream &in, HasPtr &s);

	void setInt(int value){ val = value;}
	int getInt() const{ return val;}

	void setPtr(int *p){ptr = p;}
	int* getPtr() const{ return ptr;}

	void setPtrVal(int p){ *ptr = p;}
	int getPtrVal() const{ return *ptr;}
private:
	int val;
	int *ptr;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	val = rhs.val;
	*ptr = *rhs.ptr;
	return *this;
}

ostream& operator<<(ostream &os, const HasPtr &s)
{
	os<<s.val<<"\t"
	  <<s.ptr<<"\t"
	  <<*s.ptr;
	return os;
}

istream& operator>>(istream &in, HasPtr &s)
{
	in>>s.val>>*s.ptr;
	if (!in)
		s = HasPtr();
	return in;
}

//
//void main()
//{
//	int p = 2;
//	int *p1 = new int(4);
//	HasPtr hp(1,p);
//	cout<<hp.getInt()<<" "
//		<<hp.getPtrVal()<<endl;
//	HasPtr hp1 = hp;
//	hp1.setInt(3);
//	hp1.setPtr(p1);
//	cout<<hp1.getInt()<<" "
//		<<hp1.getPtrVal()<<endl;
//
//	cout<<hp<<endl
//		<<hp1<<endl;
//	
//	cin>>hp1;
//	cout<<hp1<<endl;
//
//
//	system("PAUSE");
//}