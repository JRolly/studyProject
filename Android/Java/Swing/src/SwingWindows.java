import java.awt.Color;
import java.awt.Container;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;

public class SwingWindows extends JFrame
{
	//JFrame jf = new JFrame(title);
	//Container container = jf.getContenPane();
	public void CreateJFrame(String tital)
	{
		JFrame jf = new JFrame(tital);
		Container container = jf.getContentPane();
		JLabel jl = new JLabel("JFrame ����!");
		jl.setHorizontalAlignment(SwingConstants.CENTER);
		container.add(jl);
		container.setBackground(Color.white);
		jf.setVisible(true);
		jf.setSize(200, 150);
		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	/*
	public static void main(String[] args)
	{
		new SwingWindows().CreateJFrame("����һ��JFrame����");
	}
	*/
	
	
	
}









