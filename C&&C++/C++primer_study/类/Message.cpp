#include <iostream>
#include <set>
#include <string>

using namespace std;

//声明Message类
class Message;

/************************************************************************/
/* Folder类
 * 存储消息的文件夹
/************************************************************************/
class Folder
{
public:
	Folder(){}
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	//在指定Message的目录集中增加或删除该目录
	void save(Message&);
	void remove(Message&);

	//在该目录的消息集中增加或删除指定Message
	void addMsg(Message *msg);
	void remMsg(Message *msg);

	//获取Message
	set<Message*> getMsg() const
	{
		return this->messages;
	}
	
private:
	set<Message*> messages;

	//将目录加到形参所指的消息集中
	void put_Fldr_in_Msg(const set<Message*>&);

	//从目录所指的所有消息中删除该目录
	void remove_Fldr_in_Msg();
};


/************************************************************************/
/* Message 类  消息相关的操作                                            */
/************************************************************************/
class Message
{
public:
	//构造函数，可用作默认构造函数
	Message(const string &str = "")
		:contents(str){}

	//拷贝构造函数
	Message(const Message&);

	//重载“=”赋值运算符
	Message& operator=(const Message&);

	//析构函数
	~Message();

	//在指向给定Message的 各个Folder中删除或添加消息	
	void save(Folder&);
	void remove(Folder&);

	//在folders添加或删除
	void addFldr(Folder *fldr);
	void remFldr(Folder *fldr);

	//写入消息
	void setCntns(string str);

	//获取消息
	string getCntns() const;

private:
	string contents;
	set<Folder*> folders;

	//将自身消息副本添加到 指向给定Message的各个Folder中
	void put_Msg_in_Folders(const set<Folder*>&);

	//从folders成员的每个Folder中 删除指向给定Message的指针
	void remove_Msg_in_Folders();
};


/************************************************************************/
/* Folder类方法的实现                                                    */
/************************************************************************/
Folder::Folder(const Folder &f)
	:messages(f.messages)
{
	put_Fldr_in_Msg(messages);
}

void Folder::put_Fldr_in_Msg(const set<Message*> &rhs)
{
	for (set<Message*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++ beg)
			(*beg)->addFldr(this);
}

Folder& Folder::operator=(const Folder &rhs)
{
	if (&rhs != this)
	{
		remove_Fldr_in_Msg();
		messages = rhs.messages;
		put_Fldr_in_Msg(rhs.messages);
	}
	return *this;
}

void Folder::remove_Fldr_in_Msg()
{
	for (set<Message*>::const_iterator beg = messages.begin();
			beg != messages.end(); ++beg)
			(*beg)->remFldr(this);
}

Folder::~Folder()
{
	remove_Fldr_in_Msg();
}

void Folder::addMsg(Message *msg)
{
	messages.insert(msg);
}

void Folder::remMsg(Message *msg)
{
	messages.erase(msg);
}

void Folder::save(Message &msg)
{
	addMsg(&msg);
	msg.addFldr(this);
}

void Folder::remove(Message &msg)
{
	remMsg(&msg);
	msg.remFldr(this);
}


/************************************************************************/
/* Message 类方法的实现                                                  */
/************************************************************************/

//拷贝构造函数
Message::Message(const Message &m)
	:contents(m.contents), folders(m.folders)
{
	//将指向m的消息添加到每个Folder
	put_Msg_in_Folders(folders);
}

//将自身消息副本添加到 指向给定Message的各个Folder中
void Message::put_Msg_in_Folders(const set<Folder*> &rhs)
{
	for (set<Folder*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++ beg)
			(*beg)->addMsg(this);
}

//重载复制运算符
Message& Message::operator=(const Message &rhs)
{
	//检查是否自身赋值，若是则不进行操作
	if (&rhs != this)
	{
		remove_Msg_in_Folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}

//从folders成员的每个Folder中 删除指向给定Message的指针
void Message::remove_Msg_in_Folders()
{
	for (set<Folder*>::const_iterator beg = folders.begin();
			beg != folders.end(); ++ beg)
			(*beg)->remMsg(this);
}

Message::~Message()
{
	remove_Msg_in_Folders();
}

void Message::addFldr(Folder *fldr)
{
	folders.insert(fldr);
}

void Message::remFldr(Folder *fldr)
{
	folders.erase(fldr);
}

void Message::save(Folder &fldr)
{
	addFldr(&fldr);
	fldr.addMsg(this);
}

void Message::remove(Folder &fldr)
{
	remFldr(&fldr);
	fldr.remMsg(this);
}

void Message::setCntns(string str)
{
	contents = str;
}

string Message::getCntns() const
{
	return contents;
}
//
//void main()
//{
//	cout <<"测试Message"<<endl;
//	string str1, str2;
//	Message msg1, msg2;
//	Folder fldr1, fldr2;
//	
//	while(cin)
//	{
//		cout<<"Enter message1:";
//		cin>>str1;
//		msg1.setCntns(str1);
//		cout<<endl;
//
//		cout<<"Enter message2:";
//		cin>>str2;
//		msg2.setCntns(str2);
//		cout<<endl;
//
//		msg1.save(fldr1);
//		msg1.save(fldr2);
//		msg2.save(fldr2);		
//	}
//	//fldr1.getMsg()[0].contents;
//}