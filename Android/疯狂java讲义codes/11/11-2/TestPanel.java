
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
public class TestPanel
{
	public static void main(String[] args) 
	{
		Frame f = new Frame("测试窗口");
		//创建一个Panel对象
		Panel p = new Panel();
		//相Panel对象中添加两个组件
		p.add(new TextField(20));
		p.add(new Button("单击我"));
		f.add(p);
		//设置窗口的大小、位置
		f.setBounds(30, 30 , 250, 120);
		//将窗口显示出来（Frame对象默认处于隐藏状态）
		f.setVisible(true);
	}
}
