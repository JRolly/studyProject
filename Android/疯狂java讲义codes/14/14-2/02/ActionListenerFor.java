import java.lang.annotation.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
@Target(ElementType.FIELD)
@Retention(value=RetentionPolicy.RUNTIME)
public @interface ActionListenerFor 
{
	//定义一个成员变量，用于设置元数据
	//该listener成员变量用于保存监听器实现类
	String listener(); 
} 
