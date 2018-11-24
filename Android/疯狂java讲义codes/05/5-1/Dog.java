

/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class Dog
{
	//定义一个jump方法
	public void jump()
	{
		System.out.println("正在执行jump方法");
	}
	//定义一个run方法，run方法需要借助jump方法
	public void run()
	{
		Dog d = new Dog();
		d.jump();
		this.jump();
		System.out.println("正在执行run方法");
	}
}

