using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace MakeFunImage
{
    static public class SubtitleOnBottom
    {
        static private RectangleF _Render(Image drawTo, String text1, String text2, String text3, Int32 startX, Int32 startY, Boolean render)
        {
            Single bigFontSize = drawTo.Width * 0.04f;
            Single smallFontSize = bigFontSize * 0.9f;
            
            Int32 x = startX;
            Int32 y = startY + (Int32)bigFontSize;
            
            RectangleF textRect = SubtitleFontRenderer.DrawString
            (
                drawTo,
                bigFontSize, 
                text1,
                x, y, 
                render
            );
            
            x = (Int32)textRect.Right;
            y = (Int32)textRect.Bottom;
            
            textRect = RectangleF.Union
            (
                textRect, 
                SubtitleFontRenderer.DrawString
                (
                    drawTo,
                    smallFontSize,
                    text2,
                    x, y, 
                    render
                )
            );

            x = startX;
            y = (Int32)textRect.Bottom + (Int32)(bigFontSize + 5.0f);

            textRect = RectangleF.Union
            (
                textRect,
                SubtitleFontRenderer.DrawString
                (
                    drawTo,
                    smallFontSize,
                    text3,
                    x, y,
                    render
                )
            );
            
            return textRect;
        }
        
        static public void Render(Image drawTo, String text1, String text2, String text3, Int32 x, Int32 y)
        {
            RectangleF renderingArea = _Render
            (
                drawTo,
                text1, text2, text3,
                0, 0,
                false
            );
            
            _Render
            (
                drawTo,
                text1, text2, text3,
                x - (Int32)(renderingArea.Right / 2.0f), 
                y - (Int32)(renderingArea.Bottom / 2.0f), 
                true 
            );                
        }    
    }
}
