using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace MakeFunImage
{
    static public class TimeFontRenderer
    {
        static public RectangleF DrawString(Image drawTo, Single emSize, String text, Int32 x, Int32 y, Boolean render)
        {
            return OutlineFontRenderer.DrawString(drawTo, "HY견고딕", FontStyle.Regular, Color.Black, Color.White, emSize, emSize * 0.05f, text, x, y, render);
        }
    }
}
