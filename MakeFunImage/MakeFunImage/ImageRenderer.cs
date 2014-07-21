using System;
using System.IO;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace MakeFunImage
{
    static public class ImageRenderer
    {
        static public void DrawImage(Image drawTo, Image image, Rectangle destRect)
        {
            using (Graphics g = Graphics.FromImage(drawTo))
            {
                g.DrawImage
                (
                    image,
                    destRect,
                    new Rectangle(0, 0, image.Width, image.Height),
                    GraphicsUnit.Pixel
                );
            }
        }    
    }
}
