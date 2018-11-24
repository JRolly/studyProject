
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
public class TestProcessor
{
	public static void process(String clazz)
		throws ClassNotFoundException
	{
		int passed = 0;
		int failed = 0;
		//遍历obj对象的所有方法
		for (Method m : Class.forName(clazz).getMethods()) 
		{
			//如果包含@Testable标记注释
			if (m.isAnnotationPresent(Testable.class))
			{
				try 
				{
					//调用m方法
					m.invoke(null);
					//passed加1
					passed++;
				}
				catch (Exception ex)
				{
					System.out.printf("方法" + m + "运行失败，异常：" + ex.getCause() + "\n");
					failed++; 
				}
			}
		}
		//统计测试结果
		System.out.printf("共运行了:" + (passed + failed)+ "个方法，其中：\n" + 
			"失败了:" + failed + "个，\n" +  
			"成功了:" + passed + "个！\n"); 
	}
}
