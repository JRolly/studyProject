#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstring>

using namespace std;


string make_plural(size_t ctr, const string &word, const string &ending)
{
	return (ctr == 1)? word:word+ending;
}

class TextQuery
{
public:
	typedef vector<string>::size_type line_no;

	//每次从文件中读取一行，并将其保存在vector容器中
	void read_file(ifstream &is)
	{
		store_file(is);
		build_map();
	}

	//输入string对象，返回set对象，包含该string对象的所有行号
	set<line_no> run_query(const string&) const;


	//输入行号，返回输入文本中该行号对应的文本行
	string text_line(line_no) const;

	//输出结果
	void print_result(const set<line_no>& locs, const string& sought, 
		const TextQuery& file);

private:
	//存储输入文件
	void store_file(ifstream&);

	//将每行分解为各个单词，创建map对象，记录每个单词出现的行号
	void build_map();

	//存储输入文件
	vector<string> lines_of_text;

	//将每个单词与一个set容器关联，set容器记录该单词所在行号
	map<string, set<line_no> > word_map;

};

//存储输入文件
void TextQuery::store_file(ifstream &is)
{
	string textline;
	while(getline(is,textline))
		lines_of_text.push_back(textline);
}

//将每行分解为各个单词，创建map对象，记录每个单词出现的行号
void TextQuery::build_map()
{
	for(line_no line_num = 0; line_num != lines_of_text.size(); line_num++)
	{
		istringstream line(lines_of_text[line_num]);
		string word;
		while(line>>word)
			word_map[word].insert(line_num);
	}
}

//输入string对象，返回set对象，包含该string对象的所有行号
set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
{
	map<string, set<line_no> >::const_iterator loc = 
		word_map.find(query_word);
	if (loc == word_map.end())
		return set<line_no>();
	else
		return loc->second;
}

//输入行号，返回输入文本中该行号对应的文本行
string TextQuery::text_line(line_no line) const
{
	if (line < lines_of_text.size())
		return lines_of_text[line];
	throw std::out_of_range("line number out of range!");
}


//输出结果
void TextQuery::print_result(const set<line_no>& locs, const string& sought, 
					const TextQuery& file)
{
	typedef set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();
	cout<<"\n"<<sought<<" occurs "<<size<<" "<<make_plural(size, "time", "s")<<endl;

	line_nums::const_iterator iter = locs.begin();
	for (; iter != locs.end(); ++iter)
	{
		cout<<"\t(line"<<*iter + 1<<")"
			<<file.text_line(*iter)<<endl;
	}
}

void drive_TextQuery()
{
	ifstream infile = ifstream("inputText.txt", ios::in);
	if(!infile)
	{
		cerr<<"No input file."<<endl;
		return;
	}

	TextQuery tq;
	tq.read_file(infile);

	while(true)
	{
		cout<<"Enter a word to look for, or q to quit:";
		string s;
		cin>>s;

		if (!cin || s == "q") break;

		set<TextQuery::line_no> locs = tq.run_query(s);
		tq.print_result(locs, s, tq);
	}

}

//void main()
//{
//	cout<<"测试文本查询..."<<endl;
//	drive_TextQuery();
//	system("PAUSE");
//}
