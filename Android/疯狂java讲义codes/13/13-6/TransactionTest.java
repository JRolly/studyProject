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
public class TransactionTest
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
	public void insertInTransaction(String[] sqls)throws Exception
	{
		try
		{
			//加载驱动
			Class.forName(driver);
			//获取数据库连接
			conn = DriverManager.getConnection(url , user , pass);
			//关闭自动提交，开启事务
			conn.setAutoCommit(false);
			//使用Connection来创建一个Statment对象
			stmt = conn.createStatement();
			for (String sql : sqls)
			{
				stmt.executeUpdate(sql);
			}
			//提交事务
			conn.commit();
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
		TransactionTest tt = new TransactionTest();
		tt.initParam("mysql.ini");
		String[] sqls = new String[]{
			"insert into student_table values(null , 'aaa' ,1)",
			"insert into student_table values(null , 'bbb' ,1)",
			"insert into student_table values(null , 'ccc' ,1)",
			//下面这条SQL语句将会违反外键约束，
			//因为teacher_table中没有ID为5的记录。
			"insert into student_table values(null , 'ccc' ,5)"
		};
		tt.insertInTransaction(sqls);
	}
}
