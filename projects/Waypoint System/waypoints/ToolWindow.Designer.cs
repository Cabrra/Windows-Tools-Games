namespace midterm
{
    partial class ToolWindow
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
            this.label = new System.Windows.Forms.Label();
            this.labelTB = new System.Windows.Forms.TextBox();
            this.locationLab = new System.Windows.Forms.Label();
            this.labelX = new System.Windows.Forms.Label();
            this.labelY = new System.Windows.Forms.Label();
            this.numericX = new System.Windows.Forms.NumericUpDown();
            this.numericY = new System.Windows.Forms.NumericUpDown();
            this.buttonAdd = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericY)).BeginInit();
            this.SuspendLayout();
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Location = new System.Drawing.Point(12, 22);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(43, 17);
            this.label.TabIndex = 0;
            this.label.Text = "Label";
            // 
            // labelTB
            // 
            this.labelTB.Location = new System.Drawing.Point(61, 19);
            this.labelTB.Name = "labelTB";
            this.labelTB.Size = new System.Drawing.Size(127, 22);
            this.labelTB.TabIndex = 1;
            // 
            // locationLab
            // 
            this.locationLab.AutoSize = true;
            this.locationLab.Location = new System.Drawing.Point(34, 53);
            this.locationLab.Name = "locationLab";
            this.locationLab.Size = new System.Drawing.Size(62, 17);
            this.locationLab.TabIndex = 2;
            this.locationLab.Text = "Location";
            // 
            // labelX
            // 
            this.labelX.AutoSize = true;
            this.labelX.Location = new System.Drawing.Point(38, 86);
            this.labelX.Name = "labelX";
            this.labelX.Size = new System.Drawing.Size(17, 17);
            this.labelX.TabIndex = 3;
            this.labelX.Text = "X";
            // 
            // labelY
            // 
            this.labelY.AutoSize = true;
            this.labelY.Location = new System.Drawing.Point(38, 118);
            this.labelY.Name = "labelY";
            this.labelY.Size = new System.Drawing.Size(17, 17);
            this.labelY.TabIndex = 4;
            this.labelY.Text = "Y";
            // 
            // numericX
            // 
            this.numericX.Location = new System.Drawing.Point(68, 84);
            this.numericX.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericX.Name = "numericX";
            this.numericX.Size = new System.Drawing.Size(83, 22);
            this.numericX.TabIndex = 5;
            // 
            // numericY
            // 
            this.numericY.Location = new System.Drawing.Point(68, 116);
            this.numericY.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericY.Name = "numericY";
            this.numericY.Size = new System.Drawing.Size(83, 22);
            this.numericY.TabIndex = 6;
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(37, 160);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(136, 32);
            this.buttonAdd.TabIndex = 7;
            this.buttonAdd.Text = "Add Waitpoint";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // ToolWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(222, 204);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.numericY);
            this.Controls.Add(this.numericX);
            this.Controls.Add(this.labelY);
            this.Controls.Add(this.labelX);
            this.Controls.Add(this.locationLab);
            this.Controls.Add(this.labelTB);
            this.Controls.Add(this.label);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "ToolWindow";
            this.Text = "ToolWindow";
            ((System.ComponentModel.ISupportInitialize)(this.numericX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericY)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label;
        private System.Windows.Forms.TextBox labelTB;
        private System.Windows.Forms.Label locationLab;
        private System.Windows.Forms.Label labelX;
        private System.Windows.Forms.Label labelY;
        private System.Windows.Forms.NumericUpDown numericX;
        private System.Windows.Forms.NumericUpDown numericY;
        private System.Windows.Forms.Button buttonAdd;
    }
}