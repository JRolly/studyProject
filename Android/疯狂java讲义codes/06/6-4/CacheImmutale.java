

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class CacheImmutale
{
	private final String name;
	private static CacheImmutale[] cache = new CacheImmutale[10];
	//记录缓存实例在缓存中的位置,cache[pos-1]是最新缓存的实例
	private static int pos = 0;

	public CacheImmutale(String name)
	{
		this.name = name;
	}
	public String getName()
	{
		return name;
	}
	public static CacheImmutale valueOf(String name)
	{
		//遍历已缓存的对象，
		for (int i = 0 ; i < pos; i++)
		{
			//如果已有相同实例，直接返回该缓存的实例
			if (cache[i] != null && cache[i].getName().equals(name))
			{
				return cache[i];
			}
		}
		//如果缓存池已满
		if (pos == 10)
		{
			//把缓存的第一个对象覆盖
			cache[0] = new CacheImmutale(name);
			//把pos设为1
			pos = 1;
			return cache[0];
		}
		else
		{
			//把新创建的对象缓存起来，pos加1
			cache[pos++] = new CacheImmutale(name);
			return cache[pos - 1];		
		}
	}

	public boolean equals(Object obj)
	{
		if (obj instanceof CacheImmutale)
		{
			CacheImmutale ci = (CacheImmutale)obj;
			if (name.equals(ci.getName()))
			{
				return true;
			}
		}
		return false;
	}
	public int hashCode()
	{
		return name.hashCode();
	}
	public static void main(String[] args)
	{
		CacheImmutale c1 = CacheImmutale.valueOf("hello");
		CacheImmutale c2 = CacheImmutale.valueOf("hello");
		//下面代码将输出true
		System.out.println(c1 == c2);
	}
}
