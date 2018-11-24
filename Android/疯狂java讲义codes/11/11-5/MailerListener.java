import java.awt.*;
import java.awt.event.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class MailerListener implements ActionListener
{
	private TextField mailAddress;

	public MailerListener()	{}

	public MailerListener(TextField mailAddress)
	{
		this.mailAddress = mailAddress;
	}

	public void setMailAddress(TextField mailAddress)
	{
		this.mailAddress = mailAddress;
	}

	public void actionPerformed(ActionEvent e)
	{
		System.out.println("程序向“" + mailAddress.getText() + "”发送邮件...");
		//发送邮件的真实实现
	}
}