package sizedFrame;

import java.awt.*;
import javax.swing.*;

public class SizedFrameTest 
{
	/*public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame f = new NotHelloWorldFrame();
				f.setTitle("NotHelloWorld");						
				f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				f.setVisible(true);
				
				JFrame frame = new SizedFrame();
				frame.setTitle("SizedFrame");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
		

			}
		});
	}
	*/
}


class SizedFrame extends JFrame
{
	public SizedFrame()
	{
		//get screen dimensions
		
		Toolkit kit = Toolkit.getDefaultToolkit();
		Dimension screenSize = kit.getScreenSize();
		int screenHeight = screenSize.height;
		int screenWidth = screenSize.width;
		
		
		//set frame width,height and let platform pick screen location
		
		setSize(screenWidth/2, screenHeight/2);
		setLocationByPlatform(true);
		
		//set frame icon
		
		Image img = new ImageIcon("icon.gif").getImage();
		setIconImage(img);	
	}
}


class NotHelloWorldFrame extends JFrame
{
	public NotHelloWorldFrame()
	{
		add(new NotHelloWorldComponent());
		//pack();
		setSize(getPreferredSize().width, getPreferredSize().height);
		
	}
}

class NotHelloWorldComponent extends JComponent
{
	public static final int MESSAGE_X = 75;
	public static final int MESSAGE_Y = 100;
	
	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
	
	public void paintComponent(Graphics g)
	{
		g.drawString("Not hello, world program", MESSAGE_X, MESSAGE_Y);
	}

	public Dimension getPreferredSize(){return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);}
}














