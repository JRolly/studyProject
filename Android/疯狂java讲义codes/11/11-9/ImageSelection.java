
import java.awt.*;
import java.awt.datatransfer.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ImageSelection implements Transferable
{
	private Image image;
	public ImageSelection(Image image)
	{
		this.image = image;
	}
	public DataFlavor[] getTransferDataFlavors()
	{
		return new DataFlavor[]{DataFlavor.imageFlavor}; 
	}

	public Object getTransferData(DataFlavor flavor)
		throws UnsupportedFlavorException
	{
		if(flavor.equals(DataFlavor.imageFlavor))
		{ 
			return image;
		} 
		else
		{
			throw new UnsupportedFlavorException(flavor);
		}
	}
	public boolean isDataFlavorSupported(DataFlavor flavor)
	{
		return flavor.equals(DataFlavor.imageFlavor);
	}
} 
