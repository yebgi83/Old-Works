using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace MakeFunImage
{
    static public class OutlineFontRenderer
    {
        static public RectangleF DrawString(Image drawTo, String fontName, FontStyle fontStyle, Color outerColor, Color innerColor, Single emSize, Single strokeSize, String text, Int32 x, Int32 y, Boolean render)
        {
            using (FontFamily drawFontFamily = new FontFamily(fontName))
            {
                using (GraphicsPath drawPath = new GraphicsPath())
                {
                    drawPath.AddString (text, drawFontFamily, (Int32)fontStyle, emSize, new PointF(x, y - emSize), StringFormat.GenericDefault);

                    if (render == true)
                    {
                        using (Pen drawPen = new Pen(outerColor, strokeSize))
                        {
                            drawPen.Alignment = PenAlignment.Outset;

                            using (Brush drawBrush = new SolidBrush(innerColor))
                            {
                                using (Graphics g = Graphics.FromImage(drawTo))
                                {
                                    g.SmoothingMode = SmoothingMode.AntiAlias;
                                    g.InterpolationMode = InterpolationMode.High;
        
                                    g.DrawPath(drawPen, drawPath);
                                    g.FillPath(drawBrush, drawPath);
                                }
                            }
                        }
                    }
                    
                    return drawPath.GetBounds();
                }
            }
        }    
    }
}
