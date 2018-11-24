
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
public class TestNullLayout
{
	Frame f = new Frame("测试窗口");
	Button b1 = new Button("第一个按钮");
	Button b2 = new Button("第二个按钮");
	public void init()
	{
		f.setLayout(null);
		b1.setBounds(20, 30, 90, 28);
		f.add(b1);
		b2.setBounds(50, 45, 120, 35);
		f.add(b2);
		f.setBounds(50, 50, 200, 100);
		f.setVisible(true);
	}
	public static void main(String[] args) 
	{
		new TestNullLayout().init();
	}
}
