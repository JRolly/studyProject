#include <iostream>
#include <set>
#include <string>

using namespace std;

//����Message��
class Message;

/************************************************************************/
/* Folder��
 * �洢��Ϣ���ļ���
/************************************************************************/
class Folder
{
public:
	Folder(){}
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	//��ָ��Message��Ŀ¼�������ӻ�ɾ����Ŀ¼
	void save(Message&);
	void remove(Message&);

	//�ڸ�Ŀ¼����Ϣ�������ӻ�ɾ��ָ��Message
	void addMsg(Message *msg);
	void remMsg(Message *msg);

	//��ȡMessage
	set<Message*> getMsg() const
	{
		return this->messages;
	}
	
private:
	set<Message*> messages;

	//��Ŀ¼�ӵ��β���ָ����Ϣ����
	void put_Fldr_in_Msg(const set<Message*>&);

	//��Ŀ¼��ָ��������Ϣ��ɾ����Ŀ¼
	void remove_Fldr_in_Msg();
};


/************************************************************************/
/* Message ��  ��Ϣ��صĲ���                                            */
/************************************************************************/
class Message
{
public:
	//���캯����������Ĭ�Ϲ��캯��
	Message(const string &str = "")
		:contents(str){}

	//�������캯��
	Message(const Message&);

	//���ء�=����ֵ�����
	Message& operator=(const Message&);

	//��������
	~Message();

	//��ָ�����Message�� ����Folder��ɾ���������Ϣ	
	void save(Folder&);
	void remove(Folder&);

	//��folders��ӻ�ɾ��
	void addFldr(Folder *fldr);
	void remFldr(Folder *fldr);

	//д����Ϣ
	void setCntns(string str);

	//��ȡ��Ϣ
	string getCntns() const;

private:
	string contents;
	set<Folder*> folders;

	//��������Ϣ������ӵ� ָ�����Message�ĸ���Folder��
	void put_Msg_in_Folders(const set<Folder*>&);

	//��folders��Ա��ÿ��Folder�� ɾ��ָ�����Message��ָ��
	void remove_Msg_in_Folders();
};


/************************************************************************/
/* Folder�෽����ʵ��                                                    */
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
/* Message �෽����ʵ��                                                  */
/************************************************************************/

//�������캯��
Message::Message(const Message &m)
	:contents(m.contents), folders(m.folders)
{
	//��ָ��m����Ϣ��ӵ�ÿ��Folder
	put_Msg_in_Folders(folders);
}

//��������Ϣ������ӵ� ָ�����Message�ĸ���Folder��
void Message::put_Msg_in_Folders(const set<Folder*> &rhs)
{
	for (set<Folder*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++ beg)
			(*beg)->addMsg(this);
}

//���ظ��������
Message& Message::operator=(const Message &rhs)
{
	//����Ƿ�����ֵ�������򲻽��в���
	if (&rhs != this)
	{
		remove_Msg_in_Folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}

//��folders��Ա��ÿ��Folder�� ɾ��ָ�����Message��ָ��
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
//	cout <<"����Message"<<endl;
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