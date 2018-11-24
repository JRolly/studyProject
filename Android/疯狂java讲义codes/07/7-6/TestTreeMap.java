
import java.util.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */

//R类，重写了equals方法，如果count属性相等返回true
//重写了compareTo(Object obj)方法，如果count属性相等返回0;
class R implements Comparable
{
	int count;
	public R(int count)
	{
		this.count = count;
	}
	public String toString()
	{
		return "R(count属性:" + count + ")";
	}
	public boolean equals(Object obj)
	{
		if (this == obj)
		{
			return true;
		}
		if (obj != null 
			&& obj.getClass() == R.class)
		{
			R r = (R)obj;
			if (r.count == this.count)
			{
				return true;
			}
		}
		return false;
	}
	public int compareTo(Object obj)
	{
		R r = (R)obj;
		if (this.count > r.count)
		{
			return 1;
		}
		else if (this.count == r.count)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}
public class TestTreeMap
{
	public static void main(String[] args) 
	{
		TreeMap tm = new TreeMap();
		tm.put(new R(3) , "轻量级J2EE企业应用实战");
		tm.put(new R(-5) , "Struts2权威指南");
		tm.put(new R(9) , "ROR敏捷开发最佳实践");
		System.out.println(tm);
		//返回该TreeMap的第一个Entry对象
		System.out.println(tm.firstEntry());
		//返回该TreeMap的最后一个key值
		System.out.println(tm.lastKey());
		//返回该TreeMap的比new R(2)大的最小key值。
		System.out.println(tm.higherKey(new R(2)));
		//返回该TreeMap的比new R(2)小的最大的key－value对。
		System.out.println(tm.lowerEntry(new R(2)));
		//返回该TreeMap的子TreeMap
		System.out.println(tm.subMap(new R(-1) , new R(4)));

	}
}
