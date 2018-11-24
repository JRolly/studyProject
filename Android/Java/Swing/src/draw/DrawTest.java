package draw;

import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;

public class DrawTest
{
	/*
	public static void main(String[] args) 
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame = new DrawFrame();
				frame.setTitle("DrawTest");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			
				JFrame frame = new ImageFrame();
				frame.setTitle("Image");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
	*/
}



class DrawFrame extends JFrame
{
	public DrawFrame()
	{
		add(new DrawComponent());
		//pack();
		setSize(getPreferredSize().width, getPreferredSize().height);
	}
}

class DrawComponent extends JComponent
{
	private static final int DEFAULT_WIDTH = 400;
	private static final int DEFAULT_HEIGHT = 400;
	
	public void paintComponent(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		
		//draw a rectangle
		double leftX = 100;
		double topY = 100;
		double width = 200;
		double height = 150;
		
		Rectangle2D rect = new Rectangle2D.Double(leftX, topY, width, height);
		g2.draw(rect);
		//draw the enclosed ellipse
		Ellipse2D ellipse = new Ellipse2D.Double();
		ellipse.setFrame(rect);
		g2.draw(ellipse);
		
		//draw a diagonal line
		g2.draw(new Line2D.Double(leftX, topY, leftX+width, topY+height));
		
		//draw a circle with ths same center
		double centerX = rect.getCenterX();
		double centerY = rect.getCenterY();
		double radius = 150;
		
		Ellipse2D circle = new Ellipse2D.Double();
		circle.setFrameFromCenter(centerX, centerY, centerX+radius, centerY+radius);
		g2.draw(circle);		
	}
	
	public Dimension getPreferredSize(){return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);}
}


class ImageFrame extends JFrame
{
	public ImageFrame()
	{
		add(new ImageComponent());
		pack();
	}
}

class ImageComponent extends JComponent
{
	private static final int DEFAULT_WIDTH = 300;
	private static final int DEFAULT_HEIGHT = 200;
	
	private Image image;
	
	public ImageComponent()
	{
		image = new ImageIcon("blue-ball.gif").getImage();
	}
	
	public void paintComponent(Graphics g)
	{
		if (image == null) return;
		
		int imageWidth = image.getWidth(this);
		int imageHeight = image.getHeight(this);
		
		//draw the image in the upper-left corner
		g.drawImage(image, 0, 0, null);
		
		//tile the image across the component
		
	/*	for (int i = 0; i * imageWidth <= getWidth(); i++)
		{
			for (int j = 0; j * imageHeight <= getHeight(); j++)
			{
				if (i + j > 0)
				{
					g.copyArea(0, 0, imageWidth, imageHeight, i*imageWidth, j*imageHeight);
				}
			}
		}
	*/
	}
	
	public Dimension getPreferredSize(){return new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT);}
}





