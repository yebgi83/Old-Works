using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace MakeFunImage
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void cmdLoadBackground_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog fileDialog = new OpenFileDialog())
            {
                fileDialog.Filter = "이미지 파일|*.png;*.jpg;*.bmp";
                fileDialog.FilterIndex = 1;
                fileDialog.Title = "배경으로 가져올 이미지를 선택하세요.";
                
                if (fileDialog.ShowDialog() == DialogResult.OK)
                {
                    if (m_picPreview.Image != null)
                    {
                        m_picPreview.Image.Dispose();
                    }
                    
                    m_picPreview.Tag = fileDialog.FileName;
                    m_picPreview.Image = Image.FromFile(m_picPreview.Tag as String);
                }
            }
        }

        private void cmdRender_Click(object sender, EventArgs e)
        {
            if (m_picPreview.Image != null)
            {
                m_picPreview.Image.Dispose();
            }
                
            if (m_picPreview.Tag is String == true)
            {
                m_picPreview.Image = Image.FromFile(m_picPreview.Tag as String);
            }
            else
            {
                m_picPreview.Image = new Bitmap(m_picPreview.Width, m_picPreview.Height);
            }
            
            SubtitleOnBottom.Render
            (
                m_picPreview.Image,
                textBox1.Text,
                textBox2.Text,
                textBox3.Text,
                (Int32)(m_picPreview.Image.Width / 2.0f),
                (Int32)(m_picPreview.Image.Height * 0.8f)
            );
            
            TimeOnLeft.Render
            (
                m_picPreview.Image,
                (Int32)(m_picPreview.Image.Width * 0.02f),
                (Int32)(m_picPreview.Image.Height * 0.05f)
            );
            
            ImageRenderer.DrawImage
            (
                m_picPreview.Image,
                Properties.Resources.KBS1,
                new Rectangle
                (
                    (Int32)(m_picPreview.Image.Width * 0.875f), (Int32)(m_picPreview.Image.Height * 0.05f),
                    (Int32)(m_picPreview.Image.Width * 0.1f), (Int32)(m_picPreview.Image.Width * 0.035f)
                )
            );
        }

        private void cmdSave_Click(object sender, EventArgs e)
        {
            if (m_picPreview.Image == null)
            {
                return;
            }
            
            String savePath = Path.Combine(Application.StartupPath, Guid.NewGuid().ToString() + ".png");
        
            (m_picPreview.Image as Bitmap).Save(savePath, ImageFormat.Png);

            Process.Start("explorer.exe", "/select, " + savePath);
        }
    }
}
