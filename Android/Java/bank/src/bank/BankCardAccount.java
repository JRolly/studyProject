package bank;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Scanner;


public class BankCardAccount
{
	/*方法*/
	/*构造函数
	 * 初始化账户*/
	public BankCardAccount()
	{
		account = intToString(iAcc);
		iAcc++;		
	}
	
	/*开户
	 * 创建账户
	 * 选择开卡银行
	 * 选择地区
	 * 设置密码
	 * 默认账户余额
	 */
	public static boolean addAccount()
	{
		char[] pwd = new char[6]; 
		Scanner scanner = new Scanner(System.in);
		int i = 0;
		int index = 0;		//选择银行或地区的索引
		
		/*选择开卡银行*/				
		for(i = 0; i < BANK.length; i++)
		{/*打印可选银行*/
			System.out.print(i+1 +":"+BANK[i] + "  ");
			if(0 == ((i+1) % 5))
			{
				System.out.println("\n");
			}
		}
		System.out.println("请选择开卡银行：");
		while(true)
		{
			index = scanner.nextInt();
			if(index <= BANK.length && index >0)
			{
				bank = BANK[index-1];
				break;
			}
			else
			{
				System.out.println("输入错误！请重新输入：");
			}			
		}
		
		
		/*选择地区*/	
		for(i = 0; i < AREAS.length; i++)
		{/*打印地区*/
			System.out.print(i+1 + ":" + AREAS[i] + "  ");
			if(0 == ((i+1) % 5))
			{
				System.out.println("\n");
			}
		}
		System.out.println("\n请选择地区：");
		while(true)
		{
			index = scanner.nextInt();
			if(index <= AREAS.length && index > 0)
			{
				areas = AREAS[index-1];
				break;
			}
			else
			{
				System.out.println("输入错误！请重新输入：");
			}
		}
		
				
		/*设置姓名*/
		System.out.println("请输入您的姓名：");
		name = scanner.next();
				
		/*设置密码*/
		System.out.println("请设置6位账户密码：");
		/*循环输入密码，捕获输入过程中的异常*/
		while(true)
		{
			password = readPwd();
			System.out.println("请再次输入6为账户密码：");
			pwd = readPwd();
				
			if(Arrays.equals(pwd, password))
			{/*密码设置成功*/
				System.out.println("设置密码成功!");
				System.out.println("创建账户成功!");
				break;					
			}
			else
			{
				System.out.println("两次输入的密码不一致！");
				System.out.println("请设置6位账户密码：");			
			}	
		}		
		
		/*默认余额*/
		//this.balance = 0;
		
		/*打印账户信息*/
		//System.out.println("以下是您的账户信息：" );		
		//printAcc();
		
		return true;
	}
	
	/*存款
	 * account 账户
	 * money 存款金额
	 */
	public double deposit()
	{
		double money;
		Scanner scanner = new Scanner(System.in);
		System.out.println("请输入存款金额：");
		money = scanner.nextDouble();
		
		if(areas.equals(areas))	//存款信息需修改
		{//异地存款
			this.balance = this.balance + money - 10;
		}		
		this.balance += money;
		System.out.println("存款成功！");
		
		//scanner.close();
		return money;
	}
	
	/*取款
	 * account 账户
	 * password 密码
	 * 	money 取款金额 
	 * */
	public double draw()
	{
		double money = 0;
		char[] pwd = new char[6];
		Scanner scanner = new Scanner(System.in);
		
		/*取款前校验账户密码*/
		System.out.println("请输入账户密码：");
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				if(areas.equals(areas))/*取款所在地区信息需修改*/
				{/*同地区取款*/
					if(bank.equals(bank))/*取款所在银行信息需修改*/
					{/*同地区、同银行取款*/
						System.out.println("请输入取款金额：");
						while(true)
						{						
							money = scanner.nextDouble();
							/*取款金额必须为100的整数倍*/
							if(money % 100 == 0 && money > 0)
							{
								/*检查账户余额是否足够*/
								if(money <= this.balance)
								{	
									this.balance = this.balance - money;
									System.out.println("取款成功！");
									return money;
								}
								else
								{
									System.out.println("余额不足！请重新输入：");
								}
							}
							else
							{
								System.out.println("输入错误！取款金额必须大于0且100元的整数倍，请重新输入：");
							}
						}
					}
					else
					{/*同地区、不同银行取款*/
						System.out.println("请输入取款金额：");
						while(true)
						{
							/*取款金额必须为100的整数倍*/
							if(money % 100 == 0 && money > 0)
							{
								/*检查账户余额是否足够*/
								if(money <= this.balance - 20)
								{	
									this.balance = this.balance - money -20;
									System.out.println("取款成功！");
									return money;
								}
								else
								{
									System.out.println("余额不足！请重新输入：");
								}
							}
							else
							{
								System.out.println("输入错误！取款金额必须大于0且100元的整数倍，请重新输入：");
							}
						}
					}
						
				}	
				else
				{/*异地取款*/
					System.out.println("请输入取款金额：");
					while(true)
					{						
						money = scanner.nextDouble();
						/*取款金额必须为100的整数倍*/
						if(money % 100 == 0 && money > 0)
						{
							/*检查账户余额是否足够*/
							if(money <= this.balance - 10)
							{	
								this.balance = this.balance - money - 10;
								System.out.println("取款成功！");
								return money;
							}
							else
							{
								System.out.println("余额不足！请重新输入：");
							}
						}
						else
						{
							System.out.println("输入错误！取款金额必须大于0且100元的整数倍，请重新输入：");
						}
					}
					
				}
			}
			else
			{
				System.out.println("密码错误！请重新输入：");
			}
		}
	}
	
	/*查询
	 * password 密码
	 * */
	public void query()
	{
		char[] pwd = null;
		
		/*校验账户密码*/
		System.out.println("请输入账户密码：");		
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				//System.out.println("账户："+this.account);
				printAcc();
				System.out.printf("余额：%.2f\n",this.balance);
				return;
			}
			else
			{
				System.out.println("密码错误！请重新输入：");
			}
		}		
	}
	
	/*修改密码
	 * password 密码
	 * */
	public boolean modifyPassword()
	{
		char[] pwd = null;
		
		/*校验密码*/
		System.out.println("请输入原始密码：");
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				System.out.println("请输入新密码：");
				while(true)
				{
					password = readPwd();
					System.out.println("请确认您的密码：");
					pwd = readPwd();
					if(Arrays.equals(pwd, password))
					{
						System.out.println("密码修改成功！");
						return true;
					}
					else
					{
						System.out.println("两次输入密码不匹配，请重新输入新密码：");
					}			
				}
			}
			else
			{
				System.out.println("密码错误！请重新输入：");
			}
		}
	}
	
	/*转账
	 * bca 转入账户对象
	 * destAccount 转入账户
	 * password 密码
	 * money 转账金额*/
	public double transfer(BankCardAccount destBca)
	{
		String destAccount = null;
		char[] pwd = null;
		double money;
		Scanner scanner = new Scanner(System.in);
		
		/*读取对方账户*/
		System.out.println("请输入对方账户：");
		destAccount = this.readAcc();
		
		/*开始转账*/
		System.out.println("请输入转账金额：");
		while(true)
		{				
			money = scanner.nextDouble();
			if(!areas.equals(destBca.areas))	//地区信息需修改
			{//跨地区转账
				if(money <= this.balance - 5)
				{/*检查账户余额*/				
					System.out.println("请输入账户密码：");
					while(true)
					{/*校验账户密码*/
						pwd = readPwd();
						if(Arrays.equals(pwd, password))
						{
							/*转账成功，两个账户余额设置*/
							this.balance = this.balance - money -5;
							destBca.balance = destBca.balance + money;
							System.out.println("转账成功！");
							return money;
						}
						else
						{
							System.out.println("密码错误！请重新输入：");
						}
					}
				}
				else
				{
					System.out.println("余额不足，请重新输入转账金额：");
				}	
			}
			else
			{//同地区转账
				if(money <= this.balance - 5)
				{/*检查账户余额*/				
					System.out.println("请输入账户密码：");
					while(true)
					{/*校验账户密码*/
						pwd = readPwd();
						if(Arrays.equals(pwd, password))
						{
							/*转账成功，两个账户余额设置*/
							this.balance = this.balance - money -5;
							destBca.balance = destBca.balance + money;
							System.out.println("转账成功！");
							return money;
						}
						else
						{
							System.out.println("密码错误！请重新输入：");
						}
					}
				}
				else
				{
					System.out.println("余额不足，请重新输入转账金额：");
				}
			}
		}
	}
	
	/*读取密码*/
	public static char[] readPwd()
	{
		char[] pwd = new char[6];
		int i = 0;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try
		{
			while(i < 6)
			{
				pwd[i] = (char) br.read();
				i++;
			}		
		}catch(Exception e)
		{
			e.printStackTrace();	
		}
		return pwd;		
	}
	
	/*读取账户*/
	public String readAcc()
	{
		Integer acc;
		Scanner scanner = new Scanner(System.in);
	    acc = scanner.nextInt();
	    return BankCardAccount.intToString(acc);
	}
	
    /*打印账户信息*/
    public void printAcc()
    {
    	System.out.println("发卡银行：" + bank + "\t所属地区：" + areas);
    	System.out.printf("账户：%s\t姓名：%s\n",account,name);
    }
    
    //打印主目录
    public static void printMenu()
    {
    	System.out.println("******************************************");
    	System.out.println("*                                        *");
    	System.out.println("*  1.开户                       2.存款                                *");
    	System.out.println("*  3.取款                       4.查询                                *");
    	System.out.println("*  5.转账                       6.修改密码                         *");
    	System.out.println("*  7.退出                                                                  *");
    	System.out.println("*                                        *");
    	System.out.println("******************************************");
    }
	
	//将String型转换为Int型
    public static int stringTolnt(String intstr) {
        Integer integer;
        integer = Integer.valueOf(intstr);
        return integer.intValue();
    }

    //将Int型转换为String型
    public static String intToString(int value) {
        Integer integer = new Integer(value);
        return integer.toString();
    }
    
  //将String型转换为float型
    public static float stringToFloat(String floatstr) {
        Float floatee;
        floatee = Float.valueOf(floatstr);
        return floatee.floatValue();
    }
    
    //将float型转换为String型
    public static String floatToString(float value) {
        Float floatee = new Float(value);
        return floatee.toString();
    }
	
    
	/*域*/
	public final static String[] AREAS = {"山东","江苏","安徽","浙江","福建","上海",
					"广东","广西","海南",
					"湖北","湖南","河南","江西",
					"北京","天津","河北","山西","内蒙古",
					"宁夏","新疆","青海","陕西","甘肃",
					"四川","云南","贵州","西藏","重庆",
					"辽宁","吉林","黑龙江",
					"台湾","香港","澳门"};
	public final static String[] BANK = {"中国人民银行","中国工商银行","中国建设银行","中国银行","中国农业银行"};
	private static  String bank;
	private static  String areas;
	private final String account; 	//账户
	private static Integer iAcc = 10000001;	//初始账户
	private static String name;		//姓名
	private static char[] password; 	//密码
	private double balance = 0;		//账户余额

	
	
	public static void main(String[] args)
	{
	/*	BankCardAccount a = new BankCardAccount();
		//开户
		System.out.println("开户：");
		a.addAccount();
		System.out.println("存款：");
		double money = a.deposit();
		System.out.println("存入现金:"+money);
	//	System.out.println("取款：");
	//	money = a.draw();
	//	System.out.println("取款："+money);
	//	System.out.println("查询：");
	//	a.query();
	/*	System.out.println("修改密码：");
		a.modifyPassword();
	*/
	/*	System.out.println("开户：");
		BankCardAccount b = new BankCardAccount();
		b.addAccount();
	*/	
		/*转账*/
	/*	a.transfer(b);
		a.query();
		b.query();
	*/	
		
		int choice = 0;	//主菜单选择操作
		Scanner scanner = new Scanner(System.in);
		BankCardAccount bca = new BankCardAccount();
		
		while(true)
		{
			printMenu();	
			System.out.println("请选择操作：");
			choice = scanner.nextInt();
			switch(choice)
			{
				//开户
				case 1:
					addAccount();
					break;
				//存款
				case 2:
					bca.deposit();
					break;
				//取款
				case 3:
					bca.draw();
					break;
				//查询
				case 4:
					bca.query();
					break;
				//转账
				case 5:
					BankCardAccount destBca = new BankCardAccount();
					bca.transfer(destBca);
					break;
				//修改密码
				case 6:
					bca.modifyPassword();
					break;
				//退出
				case 7:
					return;
				default:
					System.out.println("输入错误！");
					break;
			}
		}		
	}
}







