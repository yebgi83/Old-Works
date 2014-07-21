using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace SpritePacker
{
    static public class SpriteRectHelper
    {
        static public Rectangle GetMaxTrimRect(String[] imagePaths)
        {
            if (imagePaths.Length == 0)
            {
                return new Rectangle(0, 0, 0, 0);
            }
        
            Rectangle maxTrimRect = new Rectangle(-1, -1, -1, -1);

            foreach(String imagePath in imagePaths)
            {          
                using(Bitmap bmp = Bitmap.FromFile(imagePath) as Bitmap)
                {
                    Rectangle trimRect = GetTrimRect(bmp);
                    
                    if (maxTrimRect.X == -1 || maxTrimRect.X > trimRect.X)
                    {
                        maxTrimRect.X = trimRect.X;
                    }

                    if (maxTrimRect.Y == -1 || maxTrimRect.Y > trimRect.Y)
                    {
                        maxTrimRect.Y = trimRect.Y;
                    }

                    if (maxTrimRect.Width == -1 || maxTrimRect.Width < trimRect.Width)
                    {
                        maxTrimRect.Width = trimRect.Width;
                    }

                    if (maxTrimRect.Height == -1 || maxTrimRect.Height < trimRect.Height)
                    {
                        maxTrimRect.Height = trimRect.Height;
                    }
                    
                }
            }
            
            return maxTrimRect;
        }
    
        static public Rectangle GetTrimRect(Bitmap bmp)
        {
            Rectangle trimRect = new Rectangle(-1, -1, -1, -1);

            // X
            for (Int32 x = 0; x < bmp.Width; x++)
            {
                for(Int32 y = 0; y < bmp.Height; y++)
                {
                    if (bmp.GetPixel(x, y).A != 0)
                    {
                        trimRect.X = x;
                        break; 
                    }
                }
                
                if (trimRect.X != -1) break; 
            }

            // Y
            for (Int32 y = 0; y < bmp.Height; y++)
            {
                for (Int32 x = 0; x < bmp.Width; x++)
                {
                    if (bmp.GetPixel(x, y).A != 0)
                    {
                        trimRect.Y = y;
                        break;
                    }
                }
                
                if (trimRect.Y != -1) break;
            }

            // Width
            for (Int32 x = bmp.Width - 1; x >= 0; x--)
            {
                for (Int32 y = 0; y < bmp.Height; y++)
                {
                    if (bmp.GetPixel(x, y).A != 0)
                    {
                        trimRect.Width = (x + 1) - trimRect.X;
                        break;
                    }
                }
                
                if (trimRect.Width != -1) break;
            }

            // Height
            for (Int32 y = bmp.Height - 1; y >= 0; y--)
            {
                for (Int32 x = 0; x < bmp.Width; x++)
                {
                    if (bmp.GetPixel(x, y).A != 0)
                    {
                        trimRect.Height = (y + 1) - trimRect.Y;
                        break;
                    }
                }
                
                if (trimRect.Height != -1) break;                
            }

            if (trimRect.X == -1) trimRect.X = 0;
            if (trimRect.Y == -1) trimRect.Y = 0;
            if (trimRect.Width == -1) trimRect.Width = 0;
            if (trimRect.Height == -1) trimRect.Height = 0;
            
            return trimRect; 
        }
    }
}
