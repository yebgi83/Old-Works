using System;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace MakeFunImage
{
    static public class SubtitleFontRenderer
    {
        static public RectangleF DrawString(Image drawTo, Single emSize, String text, Int32 x, Int32 y, Boolean render)
        {
            return OutlineFontRenderer.DrawString(drawTo, "HY신명조", FontStyle.Regular, Color.Black, Color.White, emSize, emSize * 0.125f, text, x, y, render);
        }
    }
}
