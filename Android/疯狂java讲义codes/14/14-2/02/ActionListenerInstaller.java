import java.awt.event.*;
import java.lang.annotation.*;
import java.lang.reflect.*;
import javax.swing.AbstractButton;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
//定义一个注释处理器类
public class ActionListenerInstaller
{
	//处理注释的方法，其中obj是包含注释的对象
	public static void processAnnotations(Object obj)
	{
		try
		{
			//获取obj对象的类
			Class cl = obj.getClass();
			//获取指定obj对象的所有Field，并遍历每个Field
			for (Field f : cl.getDeclaredFields())
			{
				//将指定Field设置成可自由访问的，避免private的Field不可访问
				f.setAccessible(true);
				//获取指定Field的、ActionListenerFor类型的注释
				ActionListenerFor a = f.getAnnotation(ActionListenerFor.class);
				if (a != null && a instanceof AbstractButton) 
				{
					//获取a注释里的元数据listner（它是一个监听器类）
					Class listenerClazz = Class.forName(a.listener());
					//使用反射来创建listner类的对象
					ActionListener al = (ActionListener)listenerClazz.newInstance();
					//获取f Field实际对应的对象
					AbstractButton ab = (AbstractButton )f.get(obj);
					//为ab对象添加事件监听器
					ab.addActionListener(al);
				}
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}
