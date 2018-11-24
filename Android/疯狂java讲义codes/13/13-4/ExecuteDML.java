import java.sql.*;
import java.util.*;
import java.io.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ExecuteDML
{
	private String driver;
	private String url;
	private String user;
	private String pass;
	Connection conn;
	Statement stmt;
	public void initParam(String paramFile)throws Exception
	{
		//使用Properties类来加载属性文件
		Properties props = new Properties();
		props.load(new FileInputStream(paramFile));
		driver = props.getProperty("driver");
		url = props.getProperty("url");
		user = props.getProperty("user");
		pass = props.getProperty("pass");
	}
	public int insertData(String sql)throws Exception
	{
		try
		{
			//加载驱动
			Class.forName(driver);
			//获取数据库连接
			conn = DriverManager.getConnection(url , user , pass);
			//使用Connection来创建一个Statment对象
			stmt = conn.createStatement();
			//执行DML,返回受影响的记录条数
			return stmt.executeUpdate(sql);
		}
		//使用finally块来关闭数据库资源
		finally
		{
			if (stmt != null)
			{
				stmt.close();
			}
			if (conn != null)
			{
				conn.close();
			}
		}
	}
	public static void main(String[] args) throws Exception
	{
		ExecuteDML ed = new ExecuteDML();
		ed.initParam("mysql.ini");
		int result = ed.insertData("insert into jdbc_test(jdbc_name,jdbc_desc)" 
			+ "select s.student_name , t.teacher_name "
			+ "from student_table s , teacher_table t "
			+ "where s.java_teacher = t.teacher_id;");
		System.out.println("------系统中共有" + result + "条记录受影响------");
	}
}
