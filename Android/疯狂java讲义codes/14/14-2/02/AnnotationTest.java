import javax.swing.*;
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
public class AnnotationTest
{
	private JFrame mainWin = new JFrame("使用注释绑定事件监听器");
	//使用注释为ok按钮绑定事件监听器
	@ActionListenerFor(listener="OkListener")
	private JButton ok = new JButton("确定");
	//使用注释为cancel按钮绑定事件监听器
	@ActionListenerFor(listener="CancelListener")
	private JButton cancel = new JButton("取消");
	
	public void init()
	{
		//初始化界面的方法
		JPanel jp = new JPanel();
		jp.add(ok);
		jp.add(cancel);
		mainWin.add(jp);
		ActionListenerInstaller.processAnnotations(this);
		mainWin.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainWin.pack();
		mainWin.setVisible(true);
	}
	public static void main(String[] args) 
	{
		new AnnotationTest().init();
	}

}
class OkListener implements ActionListener
{
	public void actionPerformed(ActionEvent evt)
	{
		JOptionPane.showMessageDialog(null , "单击了确认按钮");
	}
}
class CancelListener implements ActionListener
{
	public void actionPerformed(ActionEvent evt)
	{
		JOptionPane.showMessageDialog(null , "单击了取消按钮");
	}
}