package bank;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Scanner;


public class BankCardAccount
{
	/*����*/
	/*���캯��
	 * ��ʼ���˻�*/
	public BankCardAccount()
	{
		account = intToString(iAcc);
		iAcc++;		
	}
	
	/*����
	 * �����˻�
	 * ѡ�񿪿�����
	 * ѡ�����
	 * ��������
	 * Ĭ���˻����
	 */
	public static boolean addAccount()
	{
		char[] pwd = new char[6]; 
		Scanner scanner = new Scanner(System.in);
		int i = 0;
		int index = 0;		//ѡ�����л����������
		
		/*ѡ�񿪿�����*/				
		for(i = 0; i < BANK.length; i++)
		{/*��ӡ��ѡ����*/
			System.out.print(i+1 +":"+BANK[i] + "  ");
			if(0 == ((i+1) % 5))
			{
				System.out.println("\n");
			}
		}
		System.out.println("��ѡ�񿪿����У�");
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
				System.out.println("����������������룺");
			}			
		}
		
		
		/*ѡ�����*/	
		for(i = 0; i < AREAS.length; i++)
		{/*��ӡ����*/
			System.out.print(i+1 + ":" + AREAS[i] + "  ");
			if(0 == ((i+1) % 5))
			{
				System.out.println("\n");
			}
		}
		System.out.println("\n��ѡ�������");
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
				System.out.println("����������������룺");
			}
		}
		
				
		/*��������*/
		System.out.println("����������������");
		name = scanner.next();
				
		/*��������*/
		System.out.println("������6λ�˻����룺");
		/*ѭ���������룬������������е��쳣*/
		while(true)
		{
			password = readPwd();
			System.out.println("���ٴ�����6Ϊ�˻����룺");
			pwd = readPwd();
				
			if(Arrays.equals(pwd, password))
			{/*�������óɹ�*/
				System.out.println("��������ɹ�!");
				System.out.println("�����˻��ɹ�!");
				break;					
			}
			else
			{
				System.out.println("������������벻һ�£�");
				System.out.println("������6λ�˻����룺");			
			}	
		}		
		
		/*Ĭ�����*/
		//this.balance = 0;
		
		/*��ӡ�˻���Ϣ*/
		//System.out.println("�����������˻���Ϣ��" );		
		//printAcc();
		
		return true;
	}
	
	/*���
	 * account �˻�
	 * money �����
	 */
	public double deposit()
	{
		double money;
		Scanner scanner = new Scanner(System.in);
		System.out.println("���������");
		money = scanner.nextDouble();
		
		if(areas.equals(areas))	//�����Ϣ���޸�
		{//��ش��
			this.balance = this.balance + money - 10;
		}		
		this.balance += money;
		System.out.println("���ɹ���");
		
		//scanner.close();
		return money;
	}
	
	/*ȡ��
	 * account �˻�
	 * password ����
	 * 	money ȡ���� 
	 * */
	public double draw()
	{
		double money = 0;
		char[] pwd = new char[6];
		Scanner scanner = new Scanner(System.in);
		
		/*ȡ��ǰУ���˻�����*/
		System.out.println("�������˻����룺");
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				if(areas.equals(areas))/*ȡ�����ڵ�����Ϣ���޸�*/
				{/*ͬ����ȡ��*/
					if(bank.equals(bank))/*ȡ������������Ϣ���޸�*/
					{/*ͬ������ͬ����ȡ��*/
						System.out.println("������ȡ���");
						while(true)
						{						
							money = scanner.nextDouble();
							/*ȡ�������Ϊ100��������*/
							if(money % 100 == 0 && money > 0)
							{
								/*����˻�����Ƿ��㹻*/
								if(money <= this.balance)
								{	
									this.balance = this.balance - money;
									System.out.println("ȡ��ɹ���");
									return money;
								}
								else
								{
									System.out.println("���㣡���������룺");
								}
							}
							else
							{
								System.out.println("�������ȡ����������0��100Ԫ�������������������룺");
							}
						}
					}
					else
					{/*ͬ��������ͬ����ȡ��*/
						System.out.println("������ȡ���");
						while(true)
						{
							/*ȡ�������Ϊ100��������*/
							if(money % 100 == 0 && money > 0)
							{
								/*����˻�����Ƿ��㹻*/
								if(money <= this.balance - 20)
								{	
									this.balance = this.balance - money -20;
									System.out.println("ȡ��ɹ���");
									return money;
								}
								else
								{
									System.out.println("���㣡���������룺");
								}
							}
							else
							{
								System.out.println("�������ȡ����������0��100Ԫ�������������������룺");
							}
						}
					}
						
				}	
				else
				{/*���ȡ��*/
					System.out.println("������ȡ���");
					while(true)
					{						
						money = scanner.nextDouble();
						/*ȡ�������Ϊ100��������*/
						if(money % 100 == 0 && money > 0)
						{
							/*����˻�����Ƿ��㹻*/
							if(money <= this.balance - 10)
							{	
								this.balance = this.balance - money - 10;
								System.out.println("ȡ��ɹ���");
								return money;
							}
							else
							{
								System.out.println("���㣡���������룺");
							}
						}
						else
						{
							System.out.println("�������ȡ����������0��100Ԫ�������������������룺");
						}
					}
					
				}
			}
			else
			{
				System.out.println("����������������룺");
			}
		}
	}
	
	/*��ѯ
	 * password ����
	 * */
	public void query()
	{
		char[] pwd = null;
		
		/*У���˻�����*/
		System.out.println("�������˻����룺");		
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				//System.out.println("�˻���"+this.account);
				printAcc();
				System.out.printf("��%.2f\n",this.balance);
				return;
			}
			else
			{
				System.out.println("����������������룺");
			}
		}		
	}
	
	/*�޸�����
	 * password ����
	 * */
	public boolean modifyPassword()
	{
		char[] pwd = null;
		
		/*У������*/
		System.out.println("������ԭʼ���룺");
		while(true)
		{
			pwd = readPwd();
			if(Arrays.equals(pwd, password))
			{
				System.out.println("�����������룺");
				while(true)
				{
					password = readPwd();
					System.out.println("��ȷ���������룺");
					pwd = readPwd();
					if(Arrays.equals(pwd, password))
					{
						System.out.println("�����޸ĳɹ���");
						return true;
					}
					else
					{
						System.out.println("�����������벻ƥ�䣬���������������룺");
					}			
				}
			}
			else
			{
				System.out.println("����������������룺");
			}
		}
	}
	
	/*ת��
	 * bca ת���˻�����
	 * destAccount ת���˻�
	 * password ����
	 * money ת�˽��*/
	public double transfer(BankCardAccount destBca)
	{
		String destAccount = null;
		char[] pwd = null;
		double money;
		Scanner scanner = new Scanner(System.in);
		
		/*��ȡ�Է��˻�*/
		System.out.println("������Է��˻���");
		destAccount = this.readAcc();
		
		/*��ʼת��*/
		System.out.println("������ת�˽�");
		while(true)
		{				
			money = scanner.nextDouble();
			if(!areas.equals(destBca.areas))	//������Ϣ���޸�
			{//�����ת��
				if(money <= this.balance - 5)
				{/*����˻����*/				
					System.out.println("�������˻����룺");
					while(true)
					{/*У���˻�����*/
						pwd = readPwd();
						if(Arrays.equals(pwd, password))
						{
							/*ת�˳ɹ��������˻��������*/
							this.balance = this.balance - money -5;
							destBca.balance = destBca.balance + money;
							System.out.println("ת�˳ɹ���");
							return money;
						}
						else
						{
							System.out.println("����������������룺");
						}
					}
				}
				else
				{
					System.out.println("���㣬����������ת�˽�");
				}	
			}
			else
			{//ͬ����ת��
				if(money <= this.balance - 5)
				{/*����˻����*/				
					System.out.println("�������˻����룺");
					while(true)
					{/*У���˻�����*/
						pwd = readPwd();
						if(Arrays.equals(pwd, password))
						{
							/*ת�˳ɹ��������˻��������*/
							this.balance = this.balance - money -5;
							destBca.balance = destBca.balance + money;
							System.out.println("ת�˳ɹ���");
							return money;
						}
						else
						{
							System.out.println("����������������룺");
						}
					}
				}
				else
				{
					System.out.println("���㣬����������ת�˽�");
				}
			}
		}
	}
	
	/*��ȡ����*/
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
	
	/*��ȡ�˻�*/
	public String readAcc()
	{
		Integer acc;
		Scanner scanner = new Scanner(System.in);
	    acc = scanner.nextInt();
	    return BankCardAccount.intToString(acc);
	}
	
    /*��ӡ�˻���Ϣ*/
    public void printAcc()
    {
    	System.out.println("�������У�" + bank + "\t����������" + areas);
    	System.out.printf("�˻���%s\t������%s\n",account,name);
    }
    
    //��ӡ��Ŀ¼
    public static void printMenu()
    {
    	System.out.println("******************************************");
    	System.out.println("*                                        *");
    	System.out.println("*  1.����                       2.���                                *");
    	System.out.println("*  3.ȡ��                       4.��ѯ                                *");
    	System.out.println("*  5.ת��                       6.�޸�����                         *");
    	System.out.println("*  7.�˳�                                                                  *");
    	System.out.println("*                                        *");
    	System.out.println("******************************************");
    }
	
	//��String��ת��ΪInt��
    public static int stringTolnt(String intstr) {
        Integer integer;
        integer = Integer.valueOf(intstr);
        return integer.intValue();
    }

    //��Int��ת��ΪString��
    public static String intToString(int value) {
        Integer integer = new Integer(value);
        return integer.toString();
    }
    
  //��String��ת��Ϊfloat��
    public static float stringToFloat(String floatstr) {
        Float floatee;
        floatee = Float.valueOf(floatstr);
        return floatee.floatValue();
    }
    
    //��float��ת��ΪString��
    public static String floatToString(float value) {
        Float floatee = new Float(value);
        return floatee.toString();
    }
	
    
	/*��*/
	public final static String[] AREAS = {"ɽ��","����","����","�㽭","����","�Ϻ�",
					"�㶫","����","����",
					"����","����","����","����",
					"����","���","�ӱ�","ɽ��","���ɹ�",
					"����","�½�","�ຣ","����","����",
					"�Ĵ�","����","����","����","����",
					"����","����","������",
					"̨��","���","����"};
	public final static String[] BANK = {"�й���������","�й���������","�й���������","�й�����","�й�ũҵ����"};
	private static  String bank;
	private static  String areas;
	private final String account; 	//�˻�
	private static Integer iAcc = 10000001;	//��ʼ�˻�
	private static String name;		//����
	private static char[] password; 	//����
	private double balance = 0;		//�˻����

	
	
	public static void main(String[] args)
	{
	/*	BankCardAccount a = new BankCardAccount();
		//����
		System.out.println("������");
		a.addAccount();
		System.out.println("��");
		double money = a.deposit();
		System.out.println("�����ֽ�:"+money);
	//	System.out.println("ȡ�");
	//	money = a.draw();
	//	System.out.println("ȡ�"+money);
	//	System.out.println("��ѯ��");
	//	a.query();
	/*	System.out.println("�޸����룺");
		a.modifyPassword();
	*/
	/*	System.out.println("������");
		BankCardAccount b = new BankCardAccount();
		b.addAccount();
	*/	
		/*ת��*/
	/*	a.transfer(b);
		a.query();
		b.query();
	*/	
		
		int choice = 0;	//���˵�ѡ�����
		Scanner scanner = new Scanner(System.in);
		BankCardAccount bca = new BankCardAccount();
		
		while(true)
		{
			printMenu();	
			System.out.println("��ѡ�������");
			choice = scanner.nextInt();
			switch(choice)
			{
				//����
				case 1:
					addAccount();
					break;
				//���
				case 2:
					bca.deposit();
					break;
				//ȡ��
				case 3:
					bca.draw();
					break;
				//��ѯ
				case 4:
					bca.query();
					break;
				//ת��
				case 5:
					BankCardAccount destBca = new BankCardAccount();
					bca.transfer(destBca);
					break;
				//�޸�����
				case 6:
					bca.modifyPassword();
					break;
				//�˳�
				case 7:
					return;
				default:
					System.out.println("�������");
					break;
			}
		}		
	}
}







