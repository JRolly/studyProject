
import java.util.*;
import static java.util.Calendar.*;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class TestLenient
{
	public static void main(String[] args) 
	{
		Calendar cal = Calendar.getInstance();
		cal.set(MONTH , 13); //结果是YEAR字段加1，MONTH字段为1（二月）
		System.out.println(cal.getTime());
		//关闭容错性
		cal.setLenient(false);
		cal.set(MONTH , 13); //导致运行时异常
		System.out.println(cal.getTime());
	}
}
