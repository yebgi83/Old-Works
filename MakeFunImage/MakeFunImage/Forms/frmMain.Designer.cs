namespace MakeFunImage
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
            this.cmdLoadBackground = new System.Windows.Forms.Button();
            this.cmdRender = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.cmdSave = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.m_picPreview = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.m_picPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // cmdLoadBackground
            // 
            this.cmdLoadBackground.Location = new System.Drawing.Point(12, 12);
            this.cmdLoadBackground.Name = "cmdLoadBackground";
            this.cmdLoadBackground.Size = new System.Drawing.Size(96, 23);
            this.cmdLoadBackground.TabIndex = 1;
            this.cmdLoadBackground.Text = "배경 가져오기";
            this.cmdLoadBackground.UseVisualStyleBackColor = true;
            this.cmdLoadBackground.Click += new System.EventHandler(this.cmdLoadBackground_Click);
            // 
            // cmdRender
            // 
            this.cmdRender.Location = new System.Drawing.Point(114, 12);
            this.cmdRender.Name = "cmdRender";
            this.cmdRender.Size = new System.Drawing.Size(96, 23);
            this.cmdRender.TabIndex = 2;
            this.cmdRender.Text = "그리기";
            this.cmdRender.UseVisualStyleBackColor = true;
            this.cmdRender.Click += new System.EventHandler(this.cmdRender_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(59, 47);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(971, 21);
            this.textBox1.TabIndex = 3;
            this.textBox1.Text = "텍스트1";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(59, 74);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(971, 21);
            this.textBox2.TabIndex = 4;
            this.textBox2.Text = "텍스트2";
            // 
            // cmdSave
            // 
            this.cmdSave.Location = new System.Drawing.Point(216, 12);
            this.cmdSave.Name = "cmdSave";
            this.cmdSave.Size = new System.Drawing.Size(96, 23);
            this.cmdSave.TabIndex = 6;
            this.cmdSave.Text = "저장";
            this.cmdSave.UseVisualStyleBackColor = true;
            this.cmdSave.Click += new System.EventHandler(this.cmdSave_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(9, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 17);
            this.label1.TabIndex = 7;
            this.label1.Text = "Text1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(9, 76);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 17);
            this.label2.TabIndex = 8;
            this.label2.Text = "Text2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(9, 103);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(42, 17);
            this.label3.TabIndex = 9;
            this.label3.Text = "Text3";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(59, 101);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(971, 21);
            this.textBox3.TabIndex = 5;
            this.textBox3.Text = "텍스트3";
            // 
            // m_picPreview
            // 
            this.m_picPreview.BackColor = System.Drawing.Color.White;
            this.m_picPreview.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.m_picPreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_picPreview.Location = new System.Drawing.Point(12, 137);
            this.m_picPreview.Name = "m_picPreview";
            this.m_picPreview.Size = new System.Drawing.Size(1018, 466);
            this.m_picPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.m_picPreview.TabIndex = 10;
            this.m_picPreview.TabStop = false;
            // 
            // frmMain
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1042, 615);
            this.Controls.Add(this.m_picPreview);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cmdSave);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.cmdRender);
            this.Controls.Add(this.cmdLoadBackground);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmMain";
            this.Text = "JJBJ";
            ((System.ComponentModel.ISupportInitialize)(this.m_picPreview)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdLoadBackground;
        private System.Windows.Forms.Button cmdRender;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button cmdSave;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.PictureBox m_picPreview;
    }
}

