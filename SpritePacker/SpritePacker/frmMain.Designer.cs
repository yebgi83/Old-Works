namespace SpritePacker
{
    partial class frmMain
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_lvPackSprites = new System.Windows.Forms.ListView();
            this.m_picScrollable = new System.Windows.Forms.Panel();
            this.m_picPackPreview = new System.Windows.Forms.PictureBox();
            this.m_cmdSave = new System.Windows.Forms.Button();
            this.m_cmdDelete = new System.Windows.Forms.Button();
            this.m_picAnimationPreview = new System.Windows.Forms.PictureBox();
            this.m_tmrAnimationPreview = new System.Windows.Forms.Timer(this.components);
            this.m_picScrollable.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_picPackPreview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_picAnimationPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // m_lvPackSprites
            // 
            this.m_lvPackSprites.AllowDrop = true;
            this.m_lvPackSprites.Location = new System.Drawing.Point(12, 84);
            this.m_lvPackSprites.Name = "m_lvPackSprites";
            this.m_lvPackSprites.Size = new System.Drawing.Size(218, 236);
            this.m_lvPackSprites.TabIndex = 1;
            this.m_lvPackSprites.UseCompatibleStateImageBehavior = false;
            this.m_lvPackSprites.View = System.Windows.Forms.View.List;
            this.m_lvPackSprites.DragDrop += new System.Windows.Forms.DragEventHandler(this.m_lvPackSprites_DragDrop);
            this.m_lvPackSprites.DragEnter += new System.Windows.Forms.DragEventHandler(this.m_lvPackSprites_DragEnter);
            // 
            // m_picScrollable
            // 
            this.m_picScrollable.AutoScroll = true;
            this.m_picScrollable.BackColor = System.Drawing.Color.White;
            this.m_picScrollable.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_picScrollable.Controls.Add(this.m_picPackPreview);
            this.m_picScrollable.Location = new System.Drawing.Point(238, 12);
            this.m_picScrollable.Name = "m_picScrollable";
            this.m_picScrollable.Size = new System.Drawing.Size(670, 494);
            this.m_picScrollable.TabIndex = 2;
            // 
            // m_picPackPreview
            // 
            this.m_picPackPreview.BackColor = System.Drawing.Color.Transparent;
            this.m_picPackPreview.Location = new System.Drawing.Point(0, 0);
            this.m_picPackPreview.Name = "m_picPackPreview";
            this.m_picPackPreview.Size = new System.Drawing.Size(100, 50);
            this.m_picPackPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.m_picPackPreview.TabIndex = 0;
            this.m_picPackPreview.TabStop = false;
            // 
            // m_cmdSave
            // 
            this.m_cmdSave.Location = new System.Drawing.Point(12, 12);
            this.m_cmdSave.Name = "m_cmdSave";
            this.m_cmdSave.Size = new System.Drawing.Size(219, 30);
            this.m_cmdSave.TabIndex = 3;
            this.m_cmdSave.Text = "Save";
            this.m_cmdSave.UseVisualStyleBackColor = true;
            this.m_cmdSave.Click += new System.EventHandler(this.m_cmdSave_Click);
            // 
            // m_cmdDelete
            // 
            this.m_cmdDelete.Location = new System.Drawing.Point(12, 48);
            this.m_cmdDelete.Name = "m_cmdDelete";
            this.m_cmdDelete.Size = new System.Drawing.Size(219, 30);
            this.m_cmdDelete.TabIndex = 4;
            this.m_cmdDelete.Text = "Delete";
            this.m_cmdDelete.UseVisualStyleBackColor = true;
            this.m_cmdDelete.Click += new System.EventHandler(this.m_cmdDelete_Click);
            // 
            // m_picAnimationPreview
            // 
            this.m_picAnimationPreview.BackColor = System.Drawing.Color.White;
            this.m_picAnimationPreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_picAnimationPreview.Location = new System.Drawing.Point(12, 326);
            this.m_picAnimationPreview.Name = "m_picAnimationPreview";
            this.m_picAnimationPreview.Size = new System.Drawing.Size(217, 179);
            this.m_picAnimationPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.m_picAnimationPreview.TabIndex = 5;
            this.m_picAnimationPreview.TabStop = false;
            // 
            // m_tmrAnimationPreview
            // 
            this.m_tmrAnimationPreview.Enabled = true;
            this.m_tmrAnimationPreview.Tick += new System.EventHandler(this.m_tmrAnimationPreview_Tick);
            // 
            // frmMain
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(920, 518);
            this.Controls.Add(this.m_picAnimationPreview);
            this.Controls.Add(this.m_cmdDelete);
            this.Controls.Add(this.m_cmdSave);
            this.Controls.Add(this.m_picScrollable);
            this.Controls.Add(this.m_lvPackSprites);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmMain";
            this.Text = "Sprite Packer";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.frmMain_Paint);
            this.m_picScrollable.ResumeLayout(false);
            this.m_picScrollable.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_picPackPreview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_picAnimationPreview)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView m_lvPackSprites;
        private System.Windows.Forms.Panel m_picScrollable;
        private System.Windows.Forms.PictureBox m_picPackPreview;
        private System.Windows.Forms.Button m_cmdSave;
        private System.Windows.Forms.Button m_cmdDelete;
        private System.Windows.Forms.PictureBox m_picAnimationPreview;
        private System.Windows.Forms.Timer m_tmrAnimationPreview;
    }
}

