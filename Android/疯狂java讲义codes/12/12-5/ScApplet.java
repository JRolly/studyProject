
import javax.swing.*;
import java.applet.*;
import java.awt.*;
import java.net.*;
import java.awt.image.BufferedImage;
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
public class ScApplet extends Applet
{
	final String testStr = "Java真好玩，学习很有趣！";
	//用于保存字符串下一次出现的座标
	private int nextX;
	private int nextY;
	private Color nextColor;
	private Font nextFont;
	java.util.Random rand = new java.util.Random(System.currentTimeMillis());
	public void init()
	{
		Timer timer = new Timer(200 , new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				//随机生成下一次座标、颜色、字体大小
				nextX = rand.nextInt(400);
				nextY = rand.nextInt(300);
				nextColor = new Color(rand.nextInt(255) , rand.nextInt(255) , rand.nextInt(255));
				nextFont = new Font("Times" , Font.BOLD , rand.nextInt(60));
				//强制重绘
				repaint();
			}
		});
		timer.start();
	}
	//绘制Applet界面的方法
	public void paint(Graphics g)
	{
		g.setColor(nextColor);
		g.setFont(nextFont);
		g.drawString(testStr, nextX, nextY);
	}

	public static void main(String[] args)
	{
		JFrame jf = new JFrame();
		ScApplet panel = new ScApplet();
		panel.setPreferredSize(new Dimension(400, 300));
		panel.init();
		panel.start();
		jf.add(panel);
		jf.pack();
		jf.setVisible(true);
	}
}
