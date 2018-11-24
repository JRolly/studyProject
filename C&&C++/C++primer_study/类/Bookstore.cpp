#include <iostream>
#include <string>

using namespace std;

/************************************************************************/
/* Item_base ���� ����ʹ���ۿ۲�������ͼ��                               */
/************************************************************************/
class Item_base
{
public:
	Item_base(const string &book = "", double sales_price = 0.0):
			isbn(book), price(sales_price)
	{
		cout<<"Item_Base���캯��..."<<endl;
	}

	string book() const 
	{
		return isbn;
	}

	/*�����ض����������ܼ�*/
	virtual double net_price(size_t n) const
	{
		return n * price;
	}
	
	//���ƹ��캯��
	Item_base(const Item_base &ib) :
			isbn(ib.isbn), price(ib.price)
	{
		cout<<"Item_Base���ƹ��캯��..."<<endl;	
	}

	//���ظ��Ʋ�����
	Item_base& operator=(const Item_base &rhs)
	{
		isbn = rhs.isbn;
		price = rhs.price;
		cout<<"Item_Base���ظ��Ʋ�����..."<<endl;
		return *this;
	}

	double getPrice() const{ return price;}

	virtual ~Item_base()
	{
		cout<<"Item_Base��������..."<<endl;
	}
private:
	string isbn;
protected:
	double price;
};

/************************************************************************/
/* Bulk_item �࣬�̳�Item_base����  ������������ۿ���                   */
/************************************************************************/
class Bulk_item : public Item_base
{
public:
	Bulk_item(const string &book = "", double sales_price = 0.0,
			size_t qty = 0, double disc_rate = 0.0):
				Item_base(book, sales_price),
				min_qty(qty), discount(disc_rate)
	{
		cout<<"Bulk_item���캯��.."<<endl;			
	}
	
	//�ض��������麯��net_price��ʵ������������۲���
	//���������������ޣ���ʹ�ô��ۼ۸�
	//cnt--������
	virtual double net_price(size_t cnt) const
	{
		if (cnt >= min_qty)
		{
			return (1 - discount) * cnt * price;
		}
		else
		{
			return cnt * price;
		}
	}

	//���ƹ��캯��
	Bulk_item(const Bulk_item &bi) :
			Item_base(bi), min_qty(bi.min_qty), discount(bi.discount)
	{
		cout<<"Bulk_item���ƹ��캯��..."<<endl;
	}

	//���ظ��Ʋ�����
	Bulk_item& operator=(const Bulk_item &rhs)
	{
		if (this != &rhs)
			Item_base::operator=(rhs);
		min_qty = rhs.min_qty;
		discount = rhs.discount;
		cout<<"Bulk_item���ظ��Ʋ�����..."<<endl;
		return *this;
	}



	// �������������  
	friend ostream& operator<<(ostream &os, Bulk_item &s);

private:
	size_t min_qty;		//�ɴ��۵���С������
	double discount;	//�ۿ���
};


/************************************************************************/
/* �������������                                                         */
/************************************************************************/
ostream& operator<<(ostream &os, Bulk_item &s)
{
	os<<s.book()<<"\tԭ��:"<<s.price<<endl;
	os<<"������������"<<s.min_qty<<"������"<<10 * (1 - s.discount)<<"���Ż�";
	return os;
}

//void main()
//{
//	//Item_base base("isbn-001", 10);
//	Bulk_item bi("isbn-001", 10, 20, 0.25);
//	Item_base base = bi;
//	cout<<bi<<endl;
//	cout<<"�ܼۣ�"<<bi.net_price(20)<<endl;
//
//	cout<<base.book()<<" "<<base.getPrice()<<endl;
//
//	system("PAUSE");
//}


