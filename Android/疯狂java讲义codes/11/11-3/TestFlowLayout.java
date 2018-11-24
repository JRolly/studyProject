
import java.awt.*;
import static java.awt.FlowLayout.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestFlowLayout
{
	public static void main(String[] args) 
	{
		Frame f = new Frame("测试窗口");
		//设置Frame容器使用FlowLayout布局管理器
		f.setLayout(new FlowLayout(LEFT , 20, 5));
		//向窗口中添加10个按钮
		for (int i = 0; i < 10 ; i++ )
		{
			f.add(new Button("按钮" + i));
		}
		//设置窗口为最佳大小
		f.pack();
		//将窗口显示出来（Frame对象默认处于隐藏状态）
		f.setVisible(true);
	}
}
