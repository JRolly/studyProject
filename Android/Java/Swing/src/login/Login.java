package login;

import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class Login extends JFrame{
	JTextField jTextFieldUsername;	//定义文本框组建
	JPasswordField jPasswordFieldPassword;	//定义密码框组建
	JLabel jLabelUsername,jLabelPassword;
	JPanel jPanelUsername,jPanelPassword,jPanelButton;
	JButton jButtonOK,jButtonCancle;	//创建按钮
		
	public Login()
	{
		jTextFieldUsername = new JTextField(12);
		jPasswordFieldPassword = new JPasswordField(13);
		jLabelUsername = new JLabel("Username");
		jLabelPassword = new JLabel("Password");
		jButtonOK = new JButton("OK");
		jButtonCancle = new JButton("Cancle");
		jPanelUsername = new JPanel();
		jPanelPassword = new JPanel();
		jPanelButton = new JPanel();
		
		//设置布局
		this.setLayout(new GridLayout(3,1));
		
		//用户名面板
		jPanelUsername.add(jLabelUsername);
		jPanelUsername.add(jTextFieldUsername);
		
		//密码面板
		jPanelPassword.add(jLabelPassword);
		jPanelPassword.add(jPasswordFieldPassword);
		
		//按钮面板
		jPanelButton.add(jButtonOK);
		jPanelButton.add(jButtonCancle);
		
		//将面板添加到登录框上
		this.add(jPanelUsername);
		this.add(jPanelPassword);
		this.add(jPanelButton);
		
		//设置显示
		this.setSize(300,200);
		this.setResizable(false);
		//this.pack();
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setTitle("Login");		
		
	}
	
	
	public static void main(String[] args) 
	{
		new Login();
	}

}
