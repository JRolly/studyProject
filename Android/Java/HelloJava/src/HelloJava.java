/**
 * 
 */

/**
 * @author Jaysi
 *
 */
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;


public class HelloJava {

	/**
	 * @param args
	 */	
	public void helloJava() {
		int arr[] = {4,5,3,6,2};
		
		//数组排序
		System.out.println("排序前的数组：");
		print(arr);
		Arrays.sort(arr);
		System.out.println("排序后的数组：");
		print(arr);		
		
		System.out.println("填充数值5之前的数组：");
		print(arr);
		//填充数组
		Arrays.fill(arr,5);
		System.out.println("填充数值5之后的数组：");
		print(arr);
		
		//替换部分元素
		Arrays.fill(arr,1,3,0);
		System.out.println("替换下标为1~3(不包括3)的元素为0之后的数组：");
		print(arr);		
		
		//复制数组
		int newarr[] = Arrays.copyOf(arr,8);
		System.out.println("copyOf复制的数组为：");
		print(newarr);
		int newarr1[] = Arrays.copyOfRange(arr,2,9);
		System.out.println("copyOfRange复制的数组为：");
		print(newarr1);		
		
		//格式化日期
		Date today = new Date();
		String en_mounth = String.format(Locale.US, "%tb",today); //格式化为月份的英文缩写
		System.out.println("格式化后的月份英文缩写为："+en_mounth);
		//格式化时间
		Date date = new Date();
		System.out.println("默认时间格式为："+date);
		System.out.println("24小时制时间为："+String.format("%tH", date));
		//System.out.println("默认日期时间格式为："+date);
		System.out.println("日期和时间格式化："+String.format("%tc", date));
	
		//正则表达式
		String s = "Mk00";
		
		boolean bs = s.matches("\\p{Upper}\\p{Lower}\\d\\d");
		System.out.println("s的正则匹配结果为："+bs);
		boolean bs2 = s.matches("\\p{Upper}\\p{Lower}\\d{2}");
		System.out.println("s的正则匹配结果为："+bs2);
		
		
		//StringBuilder
		StringBuilder builder = new StringBuilder("abcdefghijk");
		builder.delete(2, 5);
		System.out.println(builder);
		builder.append("l");
		System.out.println(builder);
		builder.insert(2,"cd");
		System.out.println(builder);
		
	}
	
	/*
	 * 打印数组
	 * */
	public static void print(int arr[])
	{
		//foreach语句
		for(int e:arr)
		{
			System.out.println(e+"\t");
		}		
	}

}










