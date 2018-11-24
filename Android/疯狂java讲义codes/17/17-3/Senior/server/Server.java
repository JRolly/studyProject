import java.net.*;
import java.io.*;
import java.util.*;

/**
 * @author  yeeku.H.lee kongyeeku@163.com
 * @version  1.0
 * <br>Copyright (C), 2005-2008, yeeku.H.Lee
 * <br>This program is protected by copyright laws.
 * <br>Program Name:
 * <br>Date: 
 */
public class Server 
{
	private static final int SERVER_PORT = 30000;
	//使用MyMap对象来保存每个客户名字和对应输出流之间的对应关系。
	public static YeekuMap<String , PrintStream> clients =
		new YeekuMap<String , PrintStream>();
	public void init()
	{
		ServerSocket ss = null;
		try
		{
			//建立监听的ServerSocket
			ss = new ServerSocket(SERVER_PORT);
			//采用死循环来不断接受来自客户端的请求
			while(true)
			{
				Socket socket = ss.accept();
				new ServerThread(socket).start();
			}
		}
		//如果抛出异常
		catch (IOException ex)
		{
			System.out.println("服务器启动失败，是否端口" 
				+ SERVER_PORT + "已被占用？");
		}
		//使用finally块来关闭资源
		finally
		{
			try
			{
				if (ss != null)
				{
					ss.close();
				}
			}
			catch (IOException ex)
			{
				ex.printStackTrace();
			}
			System.exit(1);
		}
	}
    public static void main(String[] args)
    {
		Server server = new Server();
		server.init();
    }
}