import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import javax.swing.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class MonitorJOptionPane
{
	JFrame jf = new JFrame("测试JOptionPane");
	JTextArea jta = new JTextArea(5 , 40);
	JButton bn = new JButton("打开对话框");
	JOptionPane jop = new JOptionPane("测试对话框", JOptionPane.WARNING_MESSAGE
		,JOptionPane.YES_NO_CANCEL_OPTION );
	public void init()
	{
		jop.addPropertyChangeListener(new PropertyChangeListener()
		{
			public void propertyChange(PropertyChangeEvent evt)
			{
				jta.append("用户改变了选择，老选项为：" + evt.getOldValue()
					+ "\n新选项为：" + evt.getNewValue() + "!\n");
			}
		});
		bn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				jop.createDialog(jf, "测试对话框").setVisible(true);
				jta.append(jop.getValue() + "\n");
			}
		});
		jf.add(new JScrollPane(jta));
		JPanel jp = new JPanel();
		jp.add(bn);
		jf.add(jp, BorderLayout.SOUTH);
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jf.pack();
		jf.setVisible(true);
	}
	public static void main(String[] args) 
	{
		new MonitorJOptionPane().init();
	}
}
