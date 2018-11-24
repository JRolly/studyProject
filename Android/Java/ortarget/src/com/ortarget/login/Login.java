package com.ortarget.login;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Toolkit;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class Login extends JFrame
{
	JTextField jTextFieldUsername;	//�����ı����齨
	JPasswordField jPasswordFieldPassword;	//����������齨
	JLabel jLabelUsername,jLabelPassword;
	JPanel jPanelUsername,jPanelPassword,jPanelButton;
	JButton jButtonOK,jButtonCancle;	//������ť
	Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		
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
		
		//���ò���
		this.setLayout(new GridLayout(3,1));
		
		//�û������
		jPanelUsername.add(jLabelUsername);
		jPanelUsername.add(jTextFieldUsername);
		
		//�������
		jPanelPassword.add(jLabelPassword);
		jPanelPassword.add(jPasswordFieldPassword);
		
		//��ť���
		jPanelButton.add(jButtonOK);
		jPanelButton.add(jButtonCancle);
		
		//�������ӵ���¼����
		this.add(jPanelUsername);
		this.add(jPanelPassword);
		this.add(jPanelButton);
		
		//������ʾ
		//this.setSize(300,200);
		//���ô���Ĭ��Ϊ��󻯣���ȡ��Ļ�ߴ�
		//Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        this.setSize(new Dimension(screenSize.width/2,screenSize.height/2));
		//this.setResizable(false);	//���ò��ɸ��Ĵ��ڴ�С
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setTitle("Ortarget");		
		
	}
	
	
	public static void main(String[] args) 
	{
		new Login();
	}

}
