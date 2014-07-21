using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace SpritePacker
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            
            m_lvPackSprites.AllowDrop = true;
            m_lvPackSprites.ListViewItemSorter = new SpriteItemSorter();
        }

        private void frmMain_Paint(object sender, PaintEventArgs e)
        {
            if (m_lvPackSprites.Items.Count == 0)
            {
                using(Graphics g = m_lvPackSprites.CreateGraphics())
                {
                    g.DrawString
                    (
                        "여기에 이미지를 드래그 하세요.",
                        m_lvPackSprites.Font,
                        Brushes.Black,
                        new PointF(0.0f, 0.0f)
                    );
                }
            }
        }

        private void m_cmdSave_Click(object sender, EventArgs e)
        {
            String savePath = Path.Combine(Application.StartupPath, Guid.NewGuid().ToString() + ".png");
        
            if (m_lvPackSprites.Items.Count == 0)
            {
                MessageBox.Show("Sprite Image is not found.");
                return;
            }
            
            SavePackPreview(savePath);
            
            Process.Start("explorer.exe", "/select, " + savePath);
        }

        private void m_cmdDelete_Click(object sender, EventArgs e)
        {
            if (m_lvPackSprites.SelectedItems.Count == 0) 
            {
                MessageBox.Show("Selected sprite image is not found.");
                return;
            }
            
            for (Int32 index = m_lvPackSprites.SelectedIndices.Count - 1; index >= 0; index--)
            {
                m_lvPackSprites.Items.RemoveAt(m_lvPackSprites.SelectedIndices[index]);
            }
            
            Update();
            UpdatePackPreview();            
        }

        private void m_lvPackSprites_DragDrop(object sender, DragEventArgs e)
        {
            String[] dropFilePaths = null;
        
            if (e.Data.GetDataPresent(DataFormats.FileDrop) == true)
            {
                dropFilePaths = e.Data.GetData(DataFormats.FileDrop) as String[];
            }
            else
            {
                return;
            }
            
            foreach (String dropFilePath in dropFilePaths)
            {
                if (IsSupportedImagePath(dropFilePath) == false) 
                {
                    continue;
                }

                if (m_lvPackSprites.Items.ContainsKey(dropFilePath) == true) 
                {
                    continue;
                }

                ListViewItem lviNewItem = new ListViewItem()
                {
                    Name = dropFilePath,
                    Text = Path.GetFileName(dropFilePath)
                };

                m_lvPackSprites.Items.Add(lviNewItem);
            }
            
            m_lvPackSprites.Sort();

            Update();
            UpdatePackPreview();
        }

        private void m_lvPackSprites_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop) == true)
            {
                e.Effect = DragDropEffects.Move;
            }
        }
        
        private void m_tmrAnimationPreview_Tick(object sender, EventArgs e)
        {
            if (m_lvPackSprites.Items.Count > 0)
            {
                Int32 frameIndex = Convert.ToInt32(m_tmrAnimationPreview.Tag ?? 0);
                
                Int32 frameWidth = m_picPackPreview.Width / m_lvPackSprites.Items.Count;
                Int32 frameHeight = m_picPackPreview.Height;
                
                Bitmap previewBmp = new Bitmap(frameWidth, frameHeight);
                
                using(Graphics g = Graphics.FromImage(previewBmp))
                {
                    Rectangle destRect = new Rectangle(0, 0, frameWidth, frameHeight);
                    Rectangle srcRect = new Rectangle(frameWidth * frameIndex, 0, frameWidth, frameHeight);
                            
                    g.DrawImage(m_picPackPreview.Image, destRect, srcRect, GraphicsUnit.Pixel);
                }
                
                if (m_picAnimationPreview.Image != null)
                {
                    m_picAnimationPreview.Image.Dispose();
                    m_picAnimationPreview.Image = null;
                }
                
                m_picAnimationPreview.Image = previewBmp;
                
                if(frameIndex + 1 >= m_lvPackSprites.Items.Count)
                {
                    m_tmrAnimationPreview.Tag = 0;
                }
                else
                {
                    m_tmrAnimationPreview.Tag = (frameIndex + 1);
                }
            }
        }

        private Boolean IsSupportedImagePath(String path)
        {
            switch(Path.GetExtension(path).ToLower())
            {
                case ".bmp":
                case ".jpg":
                case ".png":
                    return true;
                   
                default:
                    return false;
            }                    
        }
        
        private void SavePackPreview(String savePath)
        {
            (m_picPackPreview.Image as Bitmap).Save(savePath, ImageFormat.Png);
        }        
        
        private void UpdatePackPreview()
        {
            try
            {
                List<String> packImagePaths = new List<String>();
                {
                    foreach(ListViewItem lviItem in m_lvPackSprites.Items)
                    {
                        packImagePaths.Add(lviItem.Name);
                    }
                }
                
                Rectangle maxTrimRect = SpriteRectHelper.GetMaxTrimRect(packImagePaths.ToArray());
                
                Bitmap previewBmp = new Bitmap(maxTrimRect.Width * packImagePaths.Count, maxTrimRect.Height);

                for(Int32 index = 0; index < packImagePaths.Count; index++)
                {
                    using(Graphics g = Graphics.FromImage(previewBmp))
                    {
                        using(Bitmap imageBmp = Bitmap.FromFile(packImagePaths[index]) as Bitmap)
                        {
                            Rectangle destRect = new Rectangle
                            (
                                maxTrimRect.Width * index + (maxTrimRect.Width - imageBmp.Width) / 2, 
                                (maxTrimRect.Height - imageBmp.Height) / 2, 
                                maxTrimRect.Width, 
                                maxTrimRect.Height
                            );

                            Rectangle srcRect = maxTrimRect;
                            
                            g.DrawImage(imageBmp, destRect, srcRect, GraphicsUnit.Pixel);
                        }
                    }
                }
     
                if (m_picPackPreview.Image != null)
                {
                    m_picPackPreview.Image.Dispose();
                    m_picPackPreview.Image = null;
                }
                
                m_picPackPreview.Image = previewBmp;
            }
            catch {}
        }
    }
}