using System;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms; 

namespace AvoidShit
{
    public enum Direction
    {   
        Left, Right
    }
     
    public struct SpriteFrame
    {
        public Image frameImage;
    
        public Int32 frameIndex;
        public Int32 frameWidth;
    }
    
    public struct Parameter
    {
        public Int32 health;
        public Single movementAccelation;
        public Single movementSpeed;
    }
    
    public struct Player
    {
        public PictureBox renderer;
        
        public Direction direction;

        public SpriteFrame spriteFrame;
        public Parameter parameter;
        public PointF location;
    }
    
    public struct Enemy
    {
        public PictureBox renderer;
        
        public Direction direction;

        public SpriteFrame spriteFrame;
        public Parameter parameter;
        public PointF location;
    }
}
