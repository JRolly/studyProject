

/**
 * @author  yeeku.H.lee kongyeeku@163.com
 * @version  1.0
 * <br>Copyright (C), 2005-2008, yeeku.H.Lee
 * <br>This program is protected by copyright laws.
 * <br>Program Name:
 * <br>Date: 
 */
public class TestDraw
{
    public static void main(String[] args) 
    {
		//创建一个账户
		Account acct = new Account("1234567" , 0);
		new DrawThread("取钱者" , acct , 800).start();
		new DepositThread("存钱者甲" , acct , 800).start();
		new DepositThread("存钱者乙" , acct , 800).start();
		new DepositThread("存钱者丙" , acct , 800).start();
    }
}
 