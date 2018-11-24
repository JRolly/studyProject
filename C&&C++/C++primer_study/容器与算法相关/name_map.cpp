#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;


//void name_map()
//{
//	string surname, childName;
//	map<string, vector<string> > children;
//
//	do 
//	{
//		cout<<"Enter a surname(Press Ctr+Z to end):"<<endl;
//		cin>>surname;
//
//		if (!cin)
//			break;
//
//		vector<string> chd;
//		pair<map<string, vector<string> >::iterator, bool> ret = 
//				children.insert(make_pair(surname, chd));
//
//		if (!ret.second)
//		{
//			cout<<"repeteated surname"<<surname<<endl;
//			continue;
//		}
//		
//		cout<<"Enter children's name(Press Ctr+Z to end):"<<endl;
//		while (cin>>childName)
//			ret.first->second.push_back(childName);
//
//		cin.clear();
//	} while (cin);
//
//	cin.clear();
//
//	do 
//	{
//		cout<<"Enter a surname to search(Press Ctr+Z to end):"<<endl;
//		cin>>surname;
//
//		if(!cin)
//			break;
//		
//		map<string, vector<string> >::iterator m_it = children.find(surname);
//		if (m_it == children.end())
//		{
//			cout<<"no surname!"<<endl;
//		}
//		else
//		{
//			vector<string>::iterator v_it = m_it->second.begin();
//			cout<<"Children:"<<endl;
//			while (v_it != m_it->second.end())
//				cout<<*v_it++<<endl;
//		}
//
//	} while (cin);
//}


void name_map()
{
	string surname, childName, birthday;
	map<string, vector<pair<string, string> > > children;

	do 
	{
		cout<<"Enter a surname(Press Ctr+Z to end):"<<endl;
		cin>>surname;

		if (!cin)
			break;

		vector<pair<string, string> > chd;
		pair<map<string, vector<pair<string, string> > >::iterator, bool> ret = 
			children.insert(make_pair(surname, chd));

		if (!ret.second)
		{
			cout<<"repeteated surname"<<surname<<endl;
			continue;
		}

		cout<<"Enter children's name and birthday(Press Ctr+Z to end):"<<endl;
		while (cin>>childName>>birthday)
			ret.first->second.push_back(make_pair(childName, birthday));

		cin.clear();
	} while (cin);

	cin.clear();

	do 
	{
		cout<<"Enter a surname to search(Press Ctr+Z to end):"<<endl;
		cin>>surname;

		if(!cin)
			break;

		map<string, vector<pair<string, string> > >::iterator m_it = children.find(surname);
		if (m_it == children.end())
		{
			cout<<"no surname!"<<endl;
		}
		else
		{
			vector<pair<string, string> >::iterator v_it = m_it->second.begin();
			cout<<"Children:"<<endl;
			cout<<"Name"<<"\t\tbirthday"<<endl;
			while (v_it != m_it->second.end())
			{
				cout<<v_it->first<<"\t\t"<<v_it->second<<endl;
				v_it++;
			}
		}

	} while (cin);
	cin.clear();
}


void test_count()
{
	int val;
	vector<int> vec;
	cout<<"Enter some integers(Press Ctr+Z to end.):"<<endl;
	while(cin>>val)
	{
		vec.push_back(val);
	}
	cin.clear();

	cout<<"Enter a value to count:";
	cin>>val;
	cout<<count(vec.begin(), vec.end(), val)<<" times the value "
		<<val<<endl;

	cout<<"The sum of the vector is:"<<accumulate(vec.begin(), vec.end(), 0)<<endl;
}




//void main()
//{
//	name_map();
//
//	cout<<"²âÊÔcount()º¯Êý"<<endl;
//	test_count();
//
//
//	system("PAUSE");
//}