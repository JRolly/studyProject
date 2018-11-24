
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
public class SimpleEventHandler extends WindowAdapter
{
	private Frame f = new Frame("测试");
	private TextArea ta = new TextArea(6 , 40);
	public void init()
	{
		f.addWindowListener(this);
		f.add(ta);
		f.pack();
		f.setVisible(true);
	}
	//GUI界面类直接包含事件处理器方法
	public void windowClosing(WindowEvent e) 
	{
		ta.append("用户试图关闭窗口！\n");
		System.exit(0);
	}
	public static void main(String[] args) 
	{
		new SimpleEventHandler().init();
	}
}
