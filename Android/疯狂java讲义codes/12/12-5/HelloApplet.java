
import javax.swing.*;
import java.applet.*;
import java.awt.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class HelloApplet extends JApplet
{


	//初始化Applet的方法
	public void init()
	{
		setLayout(new FlowLayout());
		add(new JButton("XXX"));
		add(new JButton("YYY"));
	}
	//启动Applet的方法
	public void start()
	{
		System.out.println("start方法");
	}
	//绘制Applet界面的方法
	public void paint(Graphics g)
	{
		super.paint(g);
		System.out.println("paint方法");
		g.drawLine(3 , 3 , 200 , 300);
	}
	//停止Applet的方法
	public void stop()
	{
		System.out.println("stop方法");
	}
	//销毁Applet的方法
	public void destroy()
	{
		System.out.println("destroy方法");
	}
	public static void main(String[] args)
	{
		JFrame jf = new JFrame();
		JApplet panel = new HelloApplet();
		panel.setPreferredSize(new Dimension(300, 400));
		//显式调用HelloApplet对象的init、start方法
		panel.init();
		panel.start();
		jf.add(panel);
		jf.pack();
		jf.setVisible(true);
	}
}
