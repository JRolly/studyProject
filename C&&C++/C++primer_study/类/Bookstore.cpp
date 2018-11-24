#include <iostream>
#include <string>

using namespace std;

/************************************************************************/
/* Item_base 基类 ，不使用折扣策略销售图书                               */
/************************************************************************/
class Item_base
{
public:
	Item_base(const string &book = "", double sales_price = 0.0):
			isbn(book), price(sales_price)
	{
		cout<<"Item_Base构造函数..."<<endl;
	}

	string book() const 
	{
		return isbn;
	}

	/*返回特定购书量的总价*/
	virtual double net_price(size_t n) const
	{
		return n * price;
	}
	
	//复制构造函数
	Item_base(const Item_base &ib) :
			isbn(ib.isbn), price(ib.price)
	{
		cout<<"Item_Base复制构造函数..."<<endl;	
	}

	//重载复制操作符
	Item_base& operator=(const Item_base &rhs)
	{
		isbn = rhs.isbn;
		price = rhs.price;
		cout<<"Item_Base重载复制操作符..."<<endl;
		return *this;
	}

	double getPrice() const{ return price;}

	virtual ~Item_base()
	{
		cout<<"Item_Base析构函数..."<<endl;
	}
private:
	string isbn;
protected:
	double price;
};

/************************************************************************/
/* Bulk_item 类，继承Item_base基类  ，批量购买的折扣类                   */
/************************************************************************/
class Bulk_item : public Item_base
{
public:
	Bulk_item(const string &book = "", double sales_price = 0.0,
			size_t qty = 0, double disc_rate = 0.0):
				Item_base(book, sales_price),
				min_qty(qty), discount(disc_rate)
	{
		cout<<"Bulk_item构造函数.."<<endl;			
	}
	
	//重定义基类的虚函数net_price，实现批量购买打折策略
	//若购书量高于下限，则使用打折价格
	//cnt--购买量
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

	//复制构造函数
	Bulk_item(const Bulk_item &bi) :
			Item_base(bi), min_qty(bi.min_qty), discount(bi.discount)
	{
		cout<<"Bulk_item复制构造函数..."<<endl;
	}

	//重载复制操作符
	Bulk_item& operator=(const Bulk_item &rhs)
	{
		if (this != &rhs)
			Item_base::operator=(rhs);
		min_qty = rhs.min_qty;
		discount = rhs.discount;
		cout<<"Bulk_item重载复制操作符..."<<endl;
		return *this;
	}



	// 重载输出操作符  
	friend ostream& operator<<(ostream &os, Bulk_item &s);

private:
	size_t min_qty;		//可打折的最小购买量
	double discount;	//折扣率
};


/************************************************************************/
/* 重载输出操作符                                                         */
/************************************************************************/
ostream& operator<<(ostream &os, Bulk_item &s)
{
	os<<s.book()<<"\t原价:"<<s.price<<endl;
	os<<"购买数量大于"<<s.min_qty<<"可享受"<<10 * (1 - s.discount)<<"折优惠";
	return os;
}

//void main()
//{
//	//Item_base base("isbn-001", 10);
//	Bulk_item bi("isbn-001", 10, 20, 0.25);
//	Item_base base = bi;
//	cout<<bi<<endl;
//	cout<<"总价："<<bi.net_price(20)<<endl;
//
//	cout<<base.book()<<" "<<base.getPrice()<<endl;
//
//	system("PAUSE");
//}


