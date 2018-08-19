namespace TileEditorSkeleton
{
    partial class ModalDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ApplyButton = new System.Windows.Forms.Button();
            this.CancelBtt = new System.Windows.Forms.Button();
            this.OKButton = new System.Windows.Forms.Button();
            this.mapGB = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.mapHeightUD = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.mapWidthUD = new System.Windows.Forms.NumericUpDown();
            this.tileSetGB = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tileSetHeightUD = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.tileSetWidthUD = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.size16RB = new System.Windows.Forms.RadioButton();
            this.size32RB = new System.Windows.Forms.RadioButton();
            this.size64RB = new System.Windows.Forms.RadioButton();
            this.importGB = new System.Windows.Forms.GroupBox();
            this.importBtn = new System.Windows.Forms.Button();
            this.miniMapView = new TileEditorSkeleton.GraphicsPanel();
            this.mapGB.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mapHeightUD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mapWidthUD)).BeginInit();
            this.tileSetGB.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tileSetHeightUD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tileSetWidthUD)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.importGB.SuspendLayout();
            this.SuspendLayout();
            // 
            // ApplyButton
            // 
            this.ApplyButton.Location = new System.Drawing.Point(173, 375);
            this.ApplyButton.Name = "ApplyButton";
            this.ApplyButton.Size = new System.Drawing.Size(99, 37);
            this.ApplyButton.TabIndex = 1;
            this.ApplyButton.Text = "Apply";
            this.ApplyButton.UseVisualStyleBackColor = true;
            this.ApplyButton.Click += new System.EventHandler(this.ApplyButton_Click);
            // 
            // CancelBtt
            // 
            this.CancelBtt.Location = new System.Drawing.Point(301, 375);
            this.CancelBtt.Name = "CancelBtt";
            this.CancelBtt.Size = new System.Drawing.Size(95, 37);
            this.CancelBtt.TabIndex = 2;
            this.CancelBtt.Text = "Cancel";
            this.CancelBtt.UseVisualStyleBackColor = true;
            // 
            // OKButton
            // 
            this.OKButton.Location = new System.Drawing.Point(43, 375);
            this.OKButton.Name = "OKButton";
            this.OKButton.Size = new System.Drawing.Size(99, 37);
            this.OKButton.TabIndex = 3;
            this.OKButton.Text = "OK";
            this.OKButton.UseVisualStyleBackColor = true;
            // 
            // mapGB
            // 
            this.mapGB.Controls.Add(this.label2);
            this.mapGB.Controls.Add(this.mapHeightUD);
            this.mapGB.Controls.Add(this.label1);
            this.mapGB.Controls.Add(this.mapWidthUD);
            this.mapGB.Location = new System.Drawing.Point(21, 172);
            this.mapGB.Name = "mapGB";
            this.mapGB.Size = new System.Drawing.Size(183, 105);
            this.mapGB.TabIndex = 4;
            this.mapGB.TabStop = false;
            this.mapGB.Text = "Map Size";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Height";
            // 
            // mapHeightUD
            // 
            this.mapHeightUD.Location = new System.Drawing.Point(79, 77);
            this.mapHeightUD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.mapHeightUD.Name = "mapHeightUD";
            this.mapHeightUD.Size = new System.Drawing.Size(67, 22);
            this.mapHeightUD.TabIndex = 2;
            this.mapHeightUD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Width";
            // 
            // mapWidthUD
            // 
            this.mapWidthUD.Location = new System.Drawing.Point(79, 34);
            this.mapWidthUD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.mapWidthUD.Name = "mapWidthUD";
            this.mapWidthUD.Size = new System.Drawing.Size(67, 22);
            this.mapWidthUD.TabIndex = 0;
            this.mapWidthUD.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // tileSetGB
            // 
            this.tileSetGB.Controls.Add(this.label3);
            this.tileSetGB.Controls.Add(this.tileSetHeightUD);
            this.tileSetGB.Controls.Add(this.label4);
            this.tileSetGB.Controls.Add(this.tileSetWidthUD);
            this.tileSetGB.Location = new System.Drawing.Point(228, 172);
            this.tileSetGB.Name = "tileSetGB";
            this.tileSetGB.Size = new System.Drawing.Size(177, 113);
            this.tileSetGB.TabIndex = 5;
            this.tileSetGB.TabStop = false;
            this.tileSetGB.Text = "Tile Set Size";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 79);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "Height";
            // 
            // tileSetHeightUD
            // 
            this.tileSetHeightUD.Location = new System.Drawing.Point(79, 77);
            this.tileSetHeightUD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.tileSetHeightUD.Name = "tileSetHeightUD";
            this.tileSetHeightUD.Size = new System.Drawing.Size(67, 22);
            this.tileSetHeightUD.TabIndex = 2;
            this.tileSetHeightUD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 36);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 17);
            this.label4.TabIndex = 1;
            this.label4.Text = "Width";
            // 
            // tileSetWidthUD
            // 
            this.tileSetWidthUD.Location = new System.Drawing.Point(79, 34);
            this.tileSetWidthUD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.tileSetWidthUD.Name = "tileSetWidthUD";
            this.tileSetWidthUD.Size = new System.Drawing.Size(67, 22);
            this.tileSetWidthUD.TabIndex = 0;
            this.tileSetWidthUD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.size16RB);
            this.groupBox1.Controls.Add(this.size32RB);
            this.groupBox1.Controls.Add(this.size64RB);
            this.groupBox1.Location = new System.Drawing.Point(21, 291);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(384, 64);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Tile Size";
            // 
            // size16RB
            // 
            this.size16RB.AutoSize = true;
            this.size16RB.Location = new System.Drawing.Point(31, 21);
            this.size16RB.Name = "size16RB";
            this.size16RB.Size = new System.Drawing.Size(67, 21);
            this.size16RB.TabIndex = 2;
            this.size16RB.TabStop = true;
            this.size16RB.Text = "16x16";
            this.size16RB.UseVisualStyleBackColor = true;
            // 
            // size32RB
            // 
            this.size32RB.AutoSize = true;
            this.size32RB.Location = new System.Drawing.Point(161, 21);
            this.size32RB.Name = "size32RB";
            this.size32RB.Size = new System.Drawing.Size(67, 21);
            this.size32RB.TabIndex = 1;
            this.size32RB.TabStop = true;
            this.size32RB.Text = "32x32";
            this.size32RB.UseVisualStyleBackColor = true;
            // 
            // size64RB
            // 
            this.size64RB.AutoSize = true;
            this.size64RB.Location = new System.Drawing.Point(289, 21);
            this.size64RB.Name = "size64RB";
            this.size64RB.Size = new System.Drawing.Size(67, 21);
            this.size64RB.TabIndex = 0;
            this.size64RB.TabStop = true;
            this.size64RB.Text = "64x64";
            this.size64RB.UseVisualStyleBackColor = true;
            // 
            // importGB
            // 
            this.importGB.Controls.Add(this.miniMapView);
            this.importGB.Controls.Add(this.importBtn);
            this.importGB.Location = new System.Drawing.Point(21, 12);
            this.importGB.Name = "importGB";
            this.importGB.Size = new System.Drawing.Size(384, 143);
            this.importGB.TabIndex = 8;
            this.importGB.TabStop = false;
            this.importGB.Text = "Import";
            // 
            // importBtn
            // 
            this.importBtn.Location = new System.Drawing.Point(268, 106);
            this.importBtn.Name = "importBtn";
            this.importBtn.Size = new System.Drawing.Size(88, 23);
            this.importBtn.TabIndex = 0;
            this.importBtn.Text = "Import";
            this.importBtn.UseVisualStyleBackColor = true;
            this.importBtn.Click += new System.EventHandler(this.importBtn_Click);
            // 
            // miniMapView
            // 
            this.miniMapView.Location = new System.Drawing.Point(48, 21);
            this.miniMapView.Name = "miniMapView";
            this.miniMapView.Size = new System.Drawing.Size(170, 108);
            this.miniMapView.TabIndex = 1;
            this.miniMapView.Paint += new System.Windows.Forms.PaintEventHandler(this.miniMapView_Paint);
            // 
            // ModalDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(427, 424);
            this.Controls.Add(this.importGB);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.tileSetGB);
            this.Controls.Add(this.mapGB);
            this.Controls.Add(this.OKButton);
            this.Controls.Add(this.CancelBtt);
            this.Controls.Add(this.ApplyButton);
            this.Name = "ModalDialog";
            this.Text = "ModalDialog";
            this.mapGB.ResumeLayout(false);
            this.mapGB.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mapHeightUD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mapWidthUD)).EndInit();
            this.tileSetGB.ResumeLayout(false);
            this.tileSetGB.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.tileSetHeightUD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tileSetWidthUD)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.importGB.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ApplyButton;
        private System.Windows.Forms.Button CancelBtt;
        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.GroupBox mapGB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown mapHeightUD;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown mapWidthUD;
        private System.Windows.Forms.GroupBox tileSetGB;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown tileSetHeightUD;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown tileSetWidthUD;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton size32RB;
        private System.Windows.Forms.RadioButton size64RB;
        private System.Windows.Forms.RadioButton size16RB;
        private System.Windows.Forms.GroupBox importGB;
        private System.Windows.Forms.Button importBtn;
        private GraphicsPanel miniMapView;
    }
}