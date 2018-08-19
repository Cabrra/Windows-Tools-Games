namespace intro
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.actionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addCharacterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.updateCharacterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.desToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeCharacterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.skillsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.skillGroup = new System.Windows.Forms.GroupBox();
            this.randomizeBtn = new System.Windows.Forms.Button();
            this.stealthNum = new System.Windows.Forms.NumericUpDown();
            this.leadershipNum = new System.Windows.Forms.NumericUpDown();
            this.knowNum = new System.Windows.Forms.NumericUpDown();
            this.healingNum = new System.Windows.Forms.NumericUpDown();
            this.enduranceNum = new System.Windows.Forms.NumericUpDown();
            this.disguiseNum = new System.Windows.Forms.NumericUpDown();
            this.cheatingNum = new System.Windows.Forms.NumericUpDown();
            this.braveryNum = new System.Windows.Forms.NumericUpDown();
            this.stealthLabel = new System.Windows.Forms.Label();
            this.leaderLabel = new System.Windows.Forms.Label();
            this.knowLabel = new System.Windows.Forms.Label();
            this.healingLabel = new System.Windows.Forms.Label();
            this.enduranceLabel = new System.Windows.Forms.Label();
            this.disguiseLabel = new System.Windows.Forms.Label();
            this.cheatingLabel = new System.Windows.Forms.Label();
            this.braveryLabel = new System.Windows.Forms.Label();
            this.basicInfoGroup = new System.Windows.Forms.GroupBox();
            this.raceCB = new System.Windows.Forms.ComboBox();
            this.ageNumberUD = new System.Windows.Forms.NumericUpDown();
            this.lastNTBox = new System.Windows.Forms.TextBox();
            this.firstNTBox = new System.Windows.Forms.TextBox();
            this.raceLabel = new System.Windows.Forms.Label();
            this.ageLabel = new System.Windows.Forms.Label();
            this.lastNLabel = new System.Windows.Forms.Label();
            this.firstNLabel = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.characterList = new System.Windows.Forms.ListBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.skillGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.stealthNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.leadershipNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.knowNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.healingNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.enduranceNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.disguiseNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cheatingNum)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.braveryNum)).BeginInit();
            this.basicInfoGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ageNumberUD)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.actionsToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(616, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.toolStripSeparator,
            this.saveAsToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(167, 24);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(167, 24);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(164, 6);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(167, 24);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(164, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(167, 24);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // actionsToolStripMenuItem
            // 
            this.actionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addCharacterToolStripMenuItem,
            this.updateCharacterToolStripMenuItem,
            this.desToolStripMenuItem,
            this.removeCharacterToolStripMenuItem});
            this.actionsToolStripMenuItem.Name = "actionsToolStripMenuItem";
            this.actionsToolStripMenuItem.Size = new System.Drawing.Size(70, 24);
            this.actionsToolStripMenuItem.Text = "Actions";
            // 
            // addCharacterToolStripMenuItem
            // 
            this.addCharacterToolStripMenuItem.Name = "addCharacterToolStripMenuItem";
            this.addCharacterToolStripMenuItem.Size = new System.Drawing.Size(202, 24);
            this.addCharacterToolStripMenuItem.Text = "Add Character";
            this.addCharacterToolStripMenuItem.Click += new System.EventHandler(this.addCharacterToolStripMenuItem_Click);
            // 
            // updateCharacterToolStripMenuItem
            // 
            this.updateCharacterToolStripMenuItem.Enabled = false;
            this.updateCharacterToolStripMenuItem.Name = "updateCharacterToolStripMenuItem";
            this.updateCharacterToolStripMenuItem.Size = new System.Drawing.Size(202, 24);
            this.updateCharacterToolStripMenuItem.Text = "Update Character";
            this.updateCharacterToolStripMenuItem.Click += new System.EventHandler(this.updateCharacterToolStripMenuItem_Click);
            // 
            // desToolStripMenuItem
            // 
            this.desToolStripMenuItem.Enabled = false;
            this.desToolStripMenuItem.Name = "desToolStripMenuItem";
            this.desToolStripMenuItem.Size = new System.Drawing.Size(202, 24);
            this.desToolStripMenuItem.Text = "Deselect Character";
            this.desToolStripMenuItem.Click += new System.EventHandler(this.desToolStripMenuItem_Click);
            // 
            // removeCharacterToolStripMenuItem
            // 
            this.removeCharacterToolStripMenuItem.Enabled = false;
            this.removeCharacterToolStripMenuItem.Name = "removeCharacterToolStripMenuItem";
            this.removeCharacterToolStripMenuItem.Size = new System.Drawing.Size(202, 24);
            this.removeCharacterToolStripMenuItem.Text = "Remove Character";
            this.removeCharacterToolStripMenuItem.Click += new System.EventHandler(this.removeCharacterToolStripMenuItem_Click);
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.skillsToolStripMenuItem});
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // skillsToolStripMenuItem
            // 
            this.skillsToolStripMenuItem.Checked = true;
            this.skillsToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.skillsToolStripMenuItem.Name = "skillsToolStripMenuItem";
            this.skillsToolStripMenuItem.Size = new System.Drawing.Size(111, 24);
            this.skillsToolStripMenuItem.Text = "Skills";
            this.skillsToolStripMenuItem.Click += new System.EventHandler(this.skillsToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(119, 24);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 28);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.AutoScroll = true;
            this.splitContainer1.Panel1.Controls.Add(this.skillGroup);
            this.splitContainer1.Panel1.Controls.Add(this.basicInfoGroup);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Size = new System.Drawing.Size(616, 506);
            this.splitContainer1.SplitterDistance = 283;
            this.splitContainer1.TabIndex = 1;
            // 
            // skillGroup
            // 
            this.skillGroup.Controls.Add(this.randomizeBtn);
            this.skillGroup.Controls.Add(this.stealthNum);
            this.skillGroup.Controls.Add(this.leadershipNum);
            this.skillGroup.Controls.Add(this.knowNum);
            this.skillGroup.Controls.Add(this.healingNum);
            this.skillGroup.Controls.Add(this.enduranceNum);
            this.skillGroup.Controls.Add(this.disguiseNum);
            this.skillGroup.Controls.Add(this.cheatingNum);
            this.skillGroup.Controls.Add(this.braveryNum);
            this.skillGroup.Controls.Add(this.stealthLabel);
            this.skillGroup.Controls.Add(this.leaderLabel);
            this.skillGroup.Controls.Add(this.knowLabel);
            this.skillGroup.Controls.Add(this.healingLabel);
            this.skillGroup.Controls.Add(this.enduranceLabel);
            this.skillGroup.Controls.Add(this.disguiseLabel);
            this.skillGroup.Controls.Add(this.cheatingLabel);
            this.skillGroup.Controls.Add(this.braveryLabel);
            this.skillGroup.Location = new System.Drawing.Point(12, 160);
            this.skillGroup.Name = "skillGroup";
            this.skillGroup.Size = new System.Drawing.Size(163, 337);
            this.skillGroup.TabIndex = 1;
            this.skillGroup.TabStop = false;
            this.skillGroup.Text = "Skills";
            // 
            // randomizeBtn
            // 
            this.randomizeBtn.Location = new System.Drawing.Point(5, 294);
            this.randomizeBtn.Name = "randomizeBtn";
            this.randomizeBtn.Size = new System.Drawing.Size(146, 27);
            this.randomizeBtn.TabIndex = 16;
            this.randomizeBtn.Text = "Randomize";
            this.randomizeBtn.UseVisualStyleBackColor = true;
            this.randomizeBtn.Click += new System.EventHandler(this.randomizeBtn_Click);
            // 
            // stealthNum
            // 
            this.stealthNum.Location = new System.Drawing.Point(87, 255);
            this.stealthNum.Name = "stealthNum";
            this.stealthNum.Size = new System.Drawing.Size(64, 22);
            this.stealthNum.TabIndex = 15;
            // 
            // leadershipNum
            // 
            this.leadershipNum.Location = new System.Drawing.Point(88, 222);
            this.leadershipNum.Name = "leadershipNum";
            this.leadershipNum.Size = new System.Drawing.Size(63, 22);
            this.leadershipNum.TabIndex = 14;
            // 
            // knowNum
            // 
            this.knowNum.Location = new System.Drawing.Point(87, 187);
            this.knowNum.Name = "knowNum";
            this.knowNum.Size = new System.Drawing.Size(64, 22);
            this.knowNum.TabIndex = 13;
            // 
            // healingNum
            // 
            this.healingNum.Location = new System.Drawing.Point(87, 155);
            this.healingNum.Name = "healingNum";
            this.healingNum.Size = new System.Drawing.Size(64, 22);
            this.healingNum.TabIndex = 12;
            // 
            // enduranceNum
            // 
            this.enduranceNum.Location = new System.Drawing.Point(87, 126);
            this.enduranceNum.Name = "enduranceNum";
            this.enduranceNum.Size = new System.Drawing.Size(64, 22);
            this.enduranceNum.TabIndex = 11;
            // 
            // disguiseNum
            // 
            this.disguiseNum.Location = new System.Drawing.Point(87, 93);
            this.disguiseNum.Name = "disguiseNum";
            this.disguiseNum.Size = new System.Drawing.Size(64, 22);
            this.disguiseNum.TabIndex = 10;
            // 
            // cheatingNum
            // 
            this.cheatingNum.Location = new System.Drawing.Point(87, 59);
            this.cheatingNum.Name = "cheatingNum";
            this.cheatingNum.Size = new System.Drawing.Size(64, 22);
            this.cheatingNum.TabIndex = 9;
            // 
            // braveryNum
            // 
            this.braveryNum.Location = new System.Drawing.Point(87, 25);
            this.braveryNum.Name = "braveryNum";
            this.braveryNum.Size = new System.Drawing.Size(64, 22);
            this.braveryNum.TabIndex = 8;
            // 
            // stealthLabel
            // 
            this.stealthLabel.AutoSize = true;
            this.stealthLabel.Location = new System.Drawing.Point(-3, 255);
            this.stealthLabel.Name = "stealthLabel";
            this.stealthLabel.Size = new System.Drawing.Size(52, 17);
            this.stealthLabel.TabIndex = 7;
            this.stealthLabel.Text = "Stealth";
            // 
            // leaderLabel
            // 
            this.leaderLabel.AutoSize = true;
            this.leaderLabel.Location = new System.Drawing.Point(-3, 222);
            this.leaderLabel.Name = "leaderLabel";
            this.leaderLabel.Size = new System.Drawing.Size(79, 17);
            this.leaderLabel.TabIndex = 6;
            this.leaderLabel.Text = "Leadership";
            // 
            // knowLabel
            // 
            this.knowLabel.AutoSize = true;
            this.knowLabel.Location = new System.Drawing.Point(-3, 192);
            this.knowLabel.Name = "knowLabel";
            this.knowLabel.Size = new System.Drawing.Size(77, 17);
            this.knowLabel.TabIndex = 5;
            this.knowLabel.Text = "Knowledge";
            // 
            // healingLabel
            // 
            this.healingLabel.AutoSize = true;
            this.healingLabel.Location = new System.Drawing.Point(-3, 160);
            this.healingLabel.Name = "healingLabel";
            this.healingLabel.Size = new System.Drawing.Size(56, 17);
            this.healingLabel.TabIndex = 4;
            this.healingLabel.Text = "Healing";
            // 
            // enduranceLabel
            // 
            this.enduranceLabel.AutoSize = true;
            this.enduranceLabel.Location = new System.Drawing.Point(-3, 131);
            this.enduranceLabel.Name = "enduranceLabel";
            this.enduranceLabel.Size = new System.Drawing.Size(77, 17);
            this.enduranceLabel.TabIndex = 3;
            this.enduranceLabel.Text = "Endurance";
            // 
            // disguiseLabel
            // 
            this.disguiseLabel.AutoSize = true;
            this.disguiseLabel.Location = new System.Drawing.Point(0, 98);
            this.disguiseLabel.Name = "disguiseLabel";
            this.disguiseLabel.Size = new System.Drawing.Size(62, 17);
            this.disguiseLabel.TabIndex = 2;
            this.disguiseLabel.Text = "Disguise";
            // 
            // cheatingLabel
            // 
            this.cheatingLabel.AutoSize = true;
            this.cheatingLabel.Location = new System.Drawing.Point(0, 64);
            this.cheatingLabel.Name = "cheatingLabel";
            this.cheatingLabel.Size = new System.Drawing.Size(64, 17);
            this.cheatingLabel.TabIndex = 1;
            this.cheatingLabel.Text = "Cheating";
            // 
            // braveryLabel
            // 
            this.braveryLabel.AutoSize = true;
            this.braveryLabel.Location = new System.Drawing.Point(0, 30);
            this.braveryLabel.Name = "braveryLabel";
            this.braveryLabel.Size = new System.Drawing.Size(57, 17);
            this.braveryLabel.TabIndex = 0;
            this.braveryLabel.Text = "Bravery";
            // 
            // basicInfoGroup
            // 
            this.basicInfoGroup.Controls.Add(this.raceCB);
            this.basicInfoGroup.Controls.Add(this.ageNumberUD);
            this.basicInfoGroup.Controls.Add(this.lastNTBox);
            this.basicInfoGroup.Controls.Add(this.firstNTBox);
            this.basicInfoGroup.Controls.Add(this.raceLabel);
            this.basicInfoGroup.Controls.Add(this.ageLabel);
            this.basicInfoGroup.Controls.Add(this.lastNLabel);
            this.basicInfoGroup.Controls.Add(this.firstNLabel);
            this.basicInfoGroup.Location = new System.Drawing.Point(12, 3);
            this.basicInfoGroup.Name = "basicInfoGroup";
            this.basicInfoGroup.Size = new System.Drawing.Size(205, 151);
            this.basicInfoGroup.TabIndex = 0;
            this.basicInfoGroup.TabStop = false;
            this.basicInfoGroup.Text = "Basic Info";
            // 
            // raceCB
            // 
            this.raceCB.FormattingEnabled = true;
            this.raceCB.Items.AddRange(new object[] {
            "None",
            "Elf",
            "Giant",
            "Hobbit",
            "Human",
            "Troll",
            "Wizard"});
            this.raceCB.Location = new System.Drawing.Point(88, 122);
            this.raceCB.Name = "raceCB";
            this.raceCB.Size = new System.Drawing.Size(100, 24);
            this.raceCB.TabIndex = 7;
            // 
            // ageNumberUD
            // 
            this.ageNumberUD.Location = new System.Drawing.Point(88, 94);
            this.ageNumberUD.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.ageNumberUD.Name = "ageNumberUD";
            this.ageNumberUD.Size = new System.Drawing.Size(100, 22);
            this.ageNumberUD.TabIndex = 6;
            // 
            // lastNTBox
            // 
            this.lastNTBox.Location = new System.Drawing.Point(88, 61);
            this.lastNTBox.Name = "lastNTBox";
            this.lastNTBox.Size = new System.Drawing.Size(100, 22);
            this.lastNTBox.TabIndex = 5;
            // 
            // firstNTBox
            // 
            this.firstNTBox.Location = new System.Drawing.Point(88, 30);
            this.firstNTBox.Name = "firstNTBox";
            this.firstNTBox.Size = new System.Drawing.Size(100, 22);
            this.firstNTBox.TabIndex = 4;
            // 
            // raceLabel
            // 
            this.raceLabel.AutoSize = true;
            this.raceLabel.Location = new System.Drawing.Point(41, 121);
            this.raceLabel.Name = "raceLabel";
            this.raceLabel.Size = new System.Drawing.Size(41, 17);
            this.raceLabel.TabIndex = 3;
            this.raceLabel.Text = "Race";
            // 
            // ageLabel
            // 
            this.ageLabel.AutoSize = true;
            this.ageLabel.Location = new System.Drawing.Point(49, 94);
            this.ageLabel.Name = "ageLabel";
            this.ageLabel.Size = new System.Drawing.Size(33, 17);
            this.ageLabel.TabIndex = 2;
            this.ageLabel.Text = "Age";
            // 
            // lastNLabel
            // 
            this.lastNLabel.AutoSize = true;
            this.lastNLabel.Location = new System.Drawing.Point(6, 61);
            this.lastNLabel.Name = "lastNLabel";
            this.lastNLabel.Size = new System.Drawing.Size(76, 17);
            this.lastNLabel.TabIndex = 1;
            this.lastNLabel.Text = "Last Name";
            // 
            // firstNLabel
            // 
            this.firstNLabel.AutoSize = true;
            this.firstNLabel.Location = new System.Drawing.Point(6, 30);
            this.firstNLabel.Name = "firstNLabel";
            this.firstNLabel.Size = new System.Drawing.Size(76, 17);
            this.firstNLabel.TabIndex = 0;
            this.firstNLabel.Text = "First Name";
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.characterList);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(329, 506);
            this.panel1.TabIndex = 0;
            // 
            // characterList
            // 
            this.characterList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.characterList.FormattingEnabled = true;
            this.characterList.ItemHeight = 16;
            this.characterList.Location = new System.Drawing.Point(0, 0);
            this.characterList.Name = "characterList";
            this.characterList.Size = new System.Drawing.Size(329, 506);
            this.characterList.TabIndex = 0;
            this.characterList.SelectedIndexChanged += new System.EventHandler(this.characterList_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(616, 534);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.Name = "Form1";
            this.Text = "Character Editor";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.skillGroup.ResumeLayout(false);
            this.skillGroup.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.stealthNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.leadershipNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.knowNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.healingNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.enduranceNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.disguiseNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cheatingNum)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.braveryNum)).EndInit();
            this.basicInfoGroup.ResumeLayout(false);
            this.basicInfoGroup.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ageNumberUD)).EndInit();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem actionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox basicInfoGroup;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ListBox characterList;
        private System.Windows.Forms.GroupBox skillGroup;
        private System.Windows.Forms.Label raceLabel;
        private System.Windows.Forms.Label ageLabel;
        private System.Windows.Forms.Label lastNLabel;
        private System.Windows.Forms.Label firstNLabel;
        private System.Windows.Forms.TextBox lastNTBox;
        private System.Windows.Forms.TextBox firstNTBox;
        private System.Windows.Forms.NumericUpDown ageNumberUD;
        private System.Windows.Forms.ComboBox raceCB;
        private System.Windows.Forms.NumericUpDown leadershipNum;
        private System.Windows.Forms.NumericUpDown knowNum;
        private System.Windows.Forms.NumericUpDown healingNum;
        private System.Windows.Forms.NumericUpDown enduranceNum;
        private System.Windows.Forms.NumericUpDown disguiseNum;
        private System.Windows.Forms.NumericUpDown cheatingNum;
        private System.Windows.Forms.NumericUpDown braveryNum;
        private System.Windows.Forms.Label stealthLabel;
        private System.Windows.Forms.Label leaderLabel;
        private System.Windows.Forms.Label knowLabel;
        private System.Windows.Forms.Label healingLabel;
        private System.Windows.Forms.Label enduranceLabel;
        private System.Windows.Forms.Label disguiseLabel;
        private System.Windows.Forms.Label cheatingLabel;
        private System.Windows.Forms.Label braveryLabel;
        private System.Windows.Forms.NumericUpDown stealthNum;
        private System.Windows.Forms.Button randomizeBtn;
        private System.Windows.Forms.ToolStripMenuItem skillsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addCharacterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem updateCharacterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem desToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeCharacterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;


    }
}

