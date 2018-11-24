
import lee.Output;
/**
 * Description:
 * <br/>Copyright (C), 2005-2008, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class OutputFactory
{
	public Output getOutput()
	{
		//下面两行代码用于控制系统到底使用Output的哪个实现类。
		//return new Printer();
		return new BetterPrinter();
	}
	public static void main(String[] args) 
	{
		OutputFactory of = new OutputFactory();
		Computer c = new Computer(of.getOutput());
		c.keyIn("轻量级J2EE企业应用实战");
		c.keyIn("Struts2权威指南");
		c.print();
	}
}
