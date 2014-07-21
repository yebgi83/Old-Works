package com.yebgi.calender;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Paint.Style;
import android.view.View;

public class androidCalenderView extends View {
	public androidCalenderView(Context context)
	{
		super(context);
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		// TODO Auto-generated method stub
		super.onDraw(canvas);
		
		// Draw the calender on the canvas of this view.
		drawCalender(canvas);
	}
	
	private final void drawCalender(Canvas canvas)
	{
		Paint paint   = new Paint();
		Rect  rectDay = new Rect(0, 0, 60, 60); 
		
		int   iDay		    = 1;
		int   maxRects 		= 7 * 5;
		int   maxRectsInRow = (getWidth() / rectDay.width()) - 1;
		int[] rectsInRow 	= new int[1 + (maxRects / maxRectsInRow)];
		 		
		// 필요한  갯수 만큼 사각형을 그린다.
		for(int rowIndex = 0, countRects = 0; countRects < maxRects; rowIndex++, countRects += maxRectsInRow)
			rectsInRow[rowIndex] = maxRectsInRow;
		
		rectsInRow[maxRects / maxRectsInRow] = maxRects % maxRectsInRow;
		
		for(int iRow = 0; iRow < rectsInRow.length; iRow++)
		{
			for(int iCol = 0; iCol < rectsInRow[iRow]; iCol++)
			{
				Rect rect = new Rect
				(
					iCol * rectDay.width(),
					iRow * rectDay.height(),
					(iCol + 1) * rectDay.width(),
					(iRow + 1) * rectDay.height()
				);
			
				paint.setStyle(Style.STROKE);
				paint.setColor(Color.YELLOW);
				
				canvas.drawRect(rect, paint);
				canvas.drawText
				(
					String.valueOf(iDay % 7), 
					rect.left + rect.width() / 2,
					rect.top + rect.height() / 2,
					paint
				);
				
				iDay++;
			}
		}
	}
}
