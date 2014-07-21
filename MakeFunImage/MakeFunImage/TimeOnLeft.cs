using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace MakeFunImage
{
    static public class TimeOnLeft
    {
        static private RectangleF _Render(Image drawTo, Int32 day, String dayName, Int32 hour, Int32 minute, Int32 startX, Int32 startY, Boolean render)
        {
            Single fontSize = drawTo.Width * 0.04f;
            
            Int32 x = startX + (Int32)(fontSize / 4);
            Int32 y = startY + (Int32)fontSize;

            RectangleF textRect1 = TimeFontRenderer.DrawString
            (
                drawTo,
                fontSize,
                Convert.ToString(day) + "(" + dayName + ")",
                x, y,
                render
            );

            x = startX;
            y = startY + (Int32)fontSize * 2;

            RectangleF textRect2 = TimeFontRenderer.DrawString
            (
                null,
                fontSize,
                Convert.ToString(hour).PadLeft(2, '0') + ":" + Convert.ToString(minute).PadLeft(2, '0'),
                x, y,
                false
            );
            
            x = (Int32)(textRect1.Right - (textRect2.Width + (fontSize / 4)));
            y = startY + (Int32)fontSize * 2;

            textRect1 = RectangleF.Union
            (
                textRect1,
                TimeFontRenderer.DrawString
                (
                    drawTo,
                    fontSize,
                    Convert.ToString(hour).PadLeft(2, '0') + ":" + Convert.ToString(minute).PadLeft(2, '0'),
                    x, y,
                    render
                )
            );    
            
            return textRect1;
        }

        static public void Render(Image drawTo, Int32 x, Int32 y)
        {
            String dayName = default(String);
            
            switch (DateTime.Now.DayOfWeek)
            {
                case DayOfWeek.Sunday:
                    dayName = "일";
                    break;
                    
                case DayOfWeek.Monday:
                    dayName = "월";
                    break;

                case DayOfWeek.Tuesday:
                    dayName = "화";
                    break;
                    
                case DayOfWeek.Wednesday:
                    dayName = "수";
                    break;
                    
                case DayOfWeek.Thursday:
                    dayName = "목";
                    break;

                case DayOfWeek.Friday:
                    dayName = "금";
                    break;
                    
                case DayOfWeek.Saturday:
                    dayName = "토";
                    break;
            }
        
            Int32 day = DateTime.Now.Day;
            Int32 hour = DateTime.Now.Hour;
            Int32 minute = DateTime.Now.Minute;
        
            RectangleF renderingArea = _Render
            (
                drawTo,
                day, dayName, hour, minute,
                0, 0,
                false
            );

            _Render
            (
                drawTo,
                day, dayName, hour, minute,
                x + (Int32)renderingArea.X,
                y + (Int32)renderingArea.Y,
                true
            );
        }    
        
    }
}
