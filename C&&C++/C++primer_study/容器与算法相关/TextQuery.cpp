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

	//ÿ�δ��ļ��ж�ȡһ�У������䱣����vector������
	void read_file(ifstream &is)
	{
		store_file(is);
		build_map();
	}

	//����string���󣬷���set���󣬰�����string����������к�
	set<line_no> run_query(const string&) const;


	//�����кţ����������ı��и��кŶ�Ӧ���ı���
	string text_line(line_no) const;

	//������
	void print_result(const set<line_no>& locs, const string& sought, 
		const TextQuery& file);

private:
	//�洢�����ļ�
	void store_file(ifstream&);

	//��ÿ�зֽ�Ϊ�������ʣ�����map���󣬼�¼ÿ�����ʳ��ֵ��к�
	void build_map();

	//�洢�����ļ�
	vector<string> lines_of_text;

	//��ÿ��������һ��set����������set������¼�õ��������к�
	map<string, set<line_no> > word_map;

};

//�洢�����ļ�
void TextQuery::store_file(ifstream &is)
{
	string textline;
	while(getline(is,textline))
		lines_of_text.push_back(textline);
}

//��ÿ�зֽ�Ϊ�������ʣ�����map���󣬼�¼ÿ�����ʳ��ֵ��к�
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

//����string���󣬷���set���󣬰�����string����������к�
set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
{
	map<string, set<line_no> >::const_iterator loc = 
		word_map.find(query_word);
	if (loc == word_map.end())
		return set<line_no>();
	else
		return loc->second;
}

//�����кţ����������ı��и��кŶ�Ӧ���ı���
string TextQuery::text_line(line_no line) const
{
	if (line < lines_of_text.size())
		return lines_of_text[line];
	throw std::out_of_range("line number out of range!");
}


//������
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
//	cout<<"�����ı���ѯ..."<<endl;
//	drive_TextQuery();
//	system("PAUSE");
//}
