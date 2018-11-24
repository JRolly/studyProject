import java.sql.*;
import java.util.*;
import java.io.*;

import static java.sql.ResultSet.*;

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class ResultSetTest
{
	private String driver;
	private String url;
	private String user;
	private String pass;
	Connection conn;
	PreparedStatement pstmt;
	ResultSet rs;
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


	public void query(String sql)throws Exception
	{
		try
		{
			//加载驱动
			Class.forName(driver);
			//获取数据库连接
			conn = DriverManager.getConnection(url , user , pass);
			//使用Connection来创建一个PreparedStatement对象
			//传入控制结果集可滚动，可更新的参数。
			pstmt = conn.prepareStatement(sql , ResultSet.TYPE_SCROLL_INSENSITIVE
				, ResultSet.CONCUR_UPDATABLE);
			rs = pstmt.executeQuery();
			rs.last();
			int rowCount = rs.getRow();
			for (int i = rowCount; i > 0 ; i-- )
			{
				rs.absolute(i);
				System.out.println(rs.getString(1) + "\t"
					+ rs.getString(2) + "\t" + rs.getString(3));
				//修改单元格多对应的值
				rs.updateString(2 , "学生名" + i);
				//提交修改
				rs.updateRow();
			}
		}
		//使用finally块来关闭数据库资源
		finally
		{
			if (rs != null)
			{
				rs.close();
			}
			if (pstmt != null)
			{
				pstmt.close();
			}
			if (conn != null)
			{
				conn.close();
			}
		}
	}
	public static void main(String[] args) throws Exception
	{
		ResultSetTest rt = new ResultSetTest();
		rt.initParam("mysql.ini");
		rt.query("select * from student_table");
	}
}
