
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
public class Canvas
{
	//同时在画布上绘制多个形状
	public void drawAll(List<? extends Shape> shapes)
	{
		for (Shape s : shapes)
		{
			s.draw(this);
		}
	}
	public static void main(String[] args)
	{
		List<Circle> circleList = new ArrayList<Circle>();
		circleList.add(new Circle());
		Canvas c = new Canvas();
		c.drawAll(circleList);
	}
}
