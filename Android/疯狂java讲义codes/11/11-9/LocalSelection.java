import java.io.*;
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
public class LocalSelection implements Transferable
{
	private Object obj;
	public LocalSelection(Object obj)
	{
		this.obj = obj;
	}
	public DataFlavor[] getTransferDataFlavors()
	{ 
		DataFlavor[] flavors = new DataFlavor[2];
		//获取被封装对象的类型
		Class clazz = obj.getClass();
		String mimeType = "application/x-java-jvm-local-objectref;class=" + clazz.getName();
		try
		{
			flavors[0] = new DataFlavor(mimeType);
			flavors[1] = DataFlavor.stringFlavor;
			return flavors;			
		}
		catch (ClassNotFoundException e)
		{
			return null;
		}
	} 

	public Object getTransferData(DataFlavor flavor)
		throws UnsupportedFlavorException
	{ 
		if(!isDataFlavorSupported(flavor))
		{ 
			throw new UnsupportedFlavorException(flavor);
		} 
		if (flavor.equals(DataFlavor.stringFlavor))
		{
			return obj.toString();
		}
		return obj;
	} 
	public boolean isDataFlavorSupported(DataFlavor flavor)
	{		
		return flavor.equals(DataFlavor.stringFlavor) ||
			flavor.getPrimaryType().equals("application")
			&& flavor.getSubType().equals("x-java-jvm-local-objectref")
			&& flavor.getRepresentationClass().isAssignableFrom(obj.getClass());
	} 
}
