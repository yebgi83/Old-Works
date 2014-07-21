using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AvoidShit
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.UserPaint, true);
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            PlayerModel.player.renderer = picPlayer;
            PlayerModel.player.direction = Direction.Right;
            PlayerModel.player.spriteFrame = new SpriteFrame();
            PlayerModel.player.spriteFrame.frameImage = Properties.Resources.player_walk;
            PlayerModel.player.spriteFrame.frameWidth = 75;
            PlayerModel.player.location.X = (ClientRectangle.Width - PlayerModel.player.spriteFrame.frameImage.Width) / 2.0f;
            PlayerModel.player.location.Y = ClientRectangle.Height - PlayerModel.player.spriteFrame.frameImage.Height;
            
            tmrPlayerAnimation.Enabled = true;
            tmrPlayerMovement.Enabled = true;
        }

        private void frmMain_KeyDown(object sender, KeyEventArgs e)
        {
            switch(e.KeyCode)
            {
                case Keys.Left:
                {
                    Single movementAccelation = PlayerModel.player.parameter.movementAccelation - 0.2f;
                    
                    if(movementAccelation <= -1.0f)
                    {
                        movementAccelation = -1.0f;
                    }
                    
                    PlayerModel.player.direction = Direction.Left;
                    PlayerModel.player.parameter.movementAccelation = movementAccelation;
                }
                break;
                    
                case Keys.Right:
                {
                    Single movementAccelation = PlayerModel.player.parameter.movementAccelation + 0.2f;
                    
                    if(movementAccelation > 1.0f)
                    {
                        movementAccelation = 1.0f;
                    }

                    PlayerModel.player.direction = Direction.Right;
                    PlayerModel.player.parameter.movementAccelation = movementAccelation;
                }
                break;
            }
        }

        private void tmrPlayerAnimation_Tick(object sender, EventArgs e)
        {
            UpdateSpriteFrame(PlayerModel.player.renderer, ref PlayerModel.player.spriteFrame, PlayerModel.player.direction);
        }
        
        private void tmrPlayerMovement_Tick(object sender, EventArgs e)
        {
            Single movementSpeed = PlayerModel.player.parameter.movementSpeed + PlayerModel.player.parameter.movementAccelation;
            
            if (movementSpeed > 5.0f) 
            {
                movementSpeed = 5.0f;
            } 
            else if (movementSpeed < -5.0f) 
            {
                movementSpeed = -5.0f;
            }
            
            PlayerModel.player.location.X += movementSpeed;
            PlayerModel.player.parameter.movementSpeed = movementSpeed;
            
            Single boundLeft = 0.0f;
            Single boundRight = ClientRectangle.Width - PlayerModel.player.renderer.Width;
            
            if (PlayerModel.player.location.X < boundLeft) 
            {
                PlayerModel.player.location.X = boundLeft;
                PlayerModel.player.parameter.movementSpeed = 0.0f;
                PlayerModel.player.parameter.movementAccelation = 0.0f;
            }
            else if (PlayerModel.player.location.X > boundRight)
            {
                PlayerModel.player.location.X = boundRight;
                PlayerModel.player.parameter.movementSpeed = 0.0f;
                PlayerModel.player.parameter.movementAccelation = 0.0f;
            }
            
            picPlayer.Top = (Int32)PlayerModel.player.location.Y;
            picPlayer.Left = (Int32)PlayerModel.player.location.X;
        }
        
        private void UpdateSpriteFrame(PictureBox renderer, ref SpriteFrame spriteFrame, Direction direction)
        {
            Int32 nextFrameIndex = spriteFrame.frameIndex + 1;
            
            if (nextFrameIndex * spriteFrame.frameWidth >= spriteFrame.frameImage.Width) 
            {
                nextFrameIndex = 0;
            }
            
            Int32 frameWidth = spriteFrame.frameWidth;
            Int32 frameHeight = spriteFrame.frameImage.Height;

            if (renderer.Image == null)
            {
                renderer.Image = new Bitmap(frameWidth, frameHeight);
                renderer.Size = renderer.Image.Size;            
            }
            
            using(Graphics g = renderer.CreateGraphics())
            {
                Rectangle destRect = new Rectangle(0, 0, frameWidth, frameHeight);
                Rectangle srcRect;
                
                if (direction == Direction.Right)
                {
                    srcRect = new Rectangle(frameWidth * nextFrameIndex, 0, frameWidth, frameHeight);
                }
                else
                {
                    srcRect = new Rectangle(frameWidth * (nextFrameIndex + 1), 0, -frameWidth, frameHeight);
                }
         
                g.Clear(Color.FromKnownColor(KnownColor.Control));       
                g.DrawImage(spriteFrame.frameImage, destRect, srcRect, GraphicsUnit.Pixel);
            }
            
            spriteFrame.frameIndex = nextFrameIndex;
        }
    }
}
