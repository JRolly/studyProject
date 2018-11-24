import com.sun.mirror.apt.*;
import com.sun.mirror.declaration.*;
import com.sun.mirror.type.*;
import com.sun.mirror.util.*;

import java.beans.*;
import java.io.*;
import java.util.*;

import java.lang.reflect.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class HibernateAnnotationProcessor implements AnnotationProcessor 
{
	//Annotation处理器环境，是该处理器与APT交互的重要途径
	private AnnotationProcessorEnvironment env;
	//构造HibernateAnnotationProcessor对象时，获得处理器环境
	public HibernateAnnotationProcessor(AnnotationProcessorEnvironment env) 
	{
		this.env = env;
	}
	//循环处理每个对象
	public void process()
	{
		//遍历每个class文件
		for (TypeDeclaration t : env.getSpecifiedTypeDeclarations())
		{
			//定义一个文件输出流，用于生成额外的文件
			FileOutputStream fos = null;
			//获取正在处理的类名
			String clazzName = t.getSimpleName();
			//获取类定义前的Persistent Annotation
			Persistent per = t.getAnnotation(Persistent.class);
			//当per Annotation不为空时才继续处理
			if(per != null)
			{
				try
				{
					//创建文件输出流
					fos = new FileOutputStream(clazzName + ".hbm.xml");
					PrintStream ps = new PrintStream(fos);
					//执行输出
					ps.println("<?xml version=\"1.0\"?>");
					ps.println("<!DOCTYPE hibernate-mapping");
					ps.println("	PUBLIC \"-//Hibernate/Hibernate Mapping DTD 3.0//EN\"");
					ps.println("    \"http://hibernate.sourceforge.net/hibernate-mapping-3.0.dtd\">");
					ps.println("<hibernate-mapping>");
					ps.print("	<class name=\"" + t);
					//输出per的table()的值
					ps.println("\" table=\"" + per.table() + "\">");
					for (FieldDeclaration f : t.getFields())
					{
						//获取指定FieldDeclaration前面的IdProperty Annotation
						IdProperty id = f.getAnnotation(IdProperty.class);
						//如果id Annotation不为空
						if (id != null)
						{
							//执行输出
							ps.println("		<id name=\""
								+ f.getSimpleName() 
								+ "\" column=\"" + id.column()
								+ "\" type=\"" + id.type()
								+ "\">");
							ps.println("			<generator class=\"" 
								+ id.generator() + "\"/>");
							ps.println("		</id>");
						}
						//获取指定FieldDeclaration前面的Property Annotation
						Property p = f.getAnnotation(Property.class);
						//如果p Annotation不为空
						if (p != null)
						{
							//执行输出
							ps.println("		<property name=\"" 
								+ f.getSimpleName() 
								+ "\" column=\"" + p.column() 
								+ "\" type=\"" + p.type()
								+ "\"/>");		
						}
					}
					ps.println("	</class>");
					ps.println("</hibernate-mapping>");
				}
				catch (Exception e)
				{
					e.printStackTrace();
				}
				finally
				{
					//关闭输出流
					try
					{
						if (fos != null)
						{
							fos.close();
						}
					}
					catch (IOException ex)
					{
						ex.printStackTrace();
					}
				}
			}
		}
	}
}
