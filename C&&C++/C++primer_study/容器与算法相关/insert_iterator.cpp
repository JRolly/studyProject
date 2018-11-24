#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;


//void main()
//{
//	int arr[] = {1,2,3,4,100,5,100};
//	vector<int> ivec(&arr[0], &arr[7]);
//	list<int> ilst;
//
//	cout<<"ivec before inserter():"<<endl;;
//	for (vector<int>::iterator it = ivec.begin();
//			it != ivec.end(); ++it)
//			cout<<*it<<" ";
//	cout<<endl;
//
//	// inserter()
//	// 将ivec复制给list容器ilst，并将ivec中值为100的元素替换为0
//	//replace_copy(ivec.begin(), ivec.end(), inserter(ilst, ilst.begin()), 100, 0);
//	//cout<<"ilst after inserter():"<<endl;
//
//	// back_inserter()
//	//replace_copy(ivec.begin(), ivec.end(), back_inserter(ilst), 100, 0);
//	//cout<<"ilst after back_inserter():"<<endl;;
//
//	// front_inserter()
//	replace_copy(ivec.begin(), ivec.end(), front_inserter(ilst), 100, 0);
//	cout<<"ilst after back_inserter():"<<endl;
//
//
//	for (list<int>::iterator it = ilst.begin();
//		it != ilst.end(); ++it)
//		cout<<*it<<" ";
//	cout<<endl;
//
//	system("PAUSE");
//}