using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace intro
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            raceCB.SelectedIndex = 0;
        }

        private void ClearFields()
        {
            firstNTBox.Text = null;
            lastNTBox.Text = null;
            ageNumberUD.Value = 0;
            raceCB.SelectedIndex = 0;

            braveryNum.Value = 0;
            cheatingNum.Value = 0;
            disguiseNum.Value = 0;
            enduranceNum.Value = 0;
            healingNum.Value = 0;
            knowNum.Value = 0;
            leadershipNum.Value = 0;
            stealthNum.Value = 0;

            updateCharacterToolStripMenuItem.Enabled = false;
            desToolStripMenuItem.Enabled = false;
            removeCharacterToolStripMenuItem.Enabled = false;
        }

        private void randomizeBtn_Click(object sender, EventArgs e)
        {
            Random random = new Random();
            braveryNum.Value = random.Next(30, 100);
            cheatingNum.Value = random.Next(30, 100);
            disguiseNum.Value = random.Next(30, 100);
            enduranceNum.Value = random.Next(30, 100);
            healingNum.Value = random.Next(30, 100);
            knowNum.Value = random.Next(30, 100);
            leadershipNum.Value = random.Next(30, 100);
            stealthNum.Value = random.Next(30, 100);
        }

        private void skillsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (skillsToolStripMenuItem.Checked)
            {
                skillGroup.Visible = false;
                skillsToolStripMenuItem.Checked = false;
            }
            else
            {
                skillGroup.Visible = true;
                skillsToolStripMenuItem.Checked = true;

            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void characterList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (characterList.SelectedIndex >= 0)
            {
                Character c = (Character)characterList.Items[characterList.SelectedIndex];

                firstNTBox.Text = c.FistName;
                lastNTBox.Text = c.LastName;
                ageNumberUD.Value = c.Age;
                raceCB.SelectedIndex = (int)c.Races;

                braveryNum.Value = c.skills.bravery;
                cheatingNum.Value = c.skills.cheating;
                disguiseNum.Value = c.skills.disguise;
                enduranceNum.Value = c.skills.endurance;
                healingNum.Value = c.skills.healing;
                knowNum.Value = c.skills.knowledge;
                leadershipNum.Value = c.skills.leadership;
                stealthNum.Value = c.skills.stealth;

                updateCharacterToolStripMenuItem.Enabled = true;
                desToolStripMenuItem.Enabled = true;
                removeCharacterToolStripMenuItem.Enabled = true;
            }

        }

        private void addCharacterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Character c = new Character();

            c.FistName = firstNTBox.Text;
            c.LastName = lastNTBox.Text;
            c.Age = ageNumberUD.Value;
            c.Races = (CharacterRace)raceCB.SelectedIndex;

            c.skills.bravery = braveryNum.Value;
            c.skills.cheating = cheatingNum.Value;
            c.skills.disguise = disguiseNum.Value;
            c.skills.endurance = enduranceNum.Value;
            c.skills.healing = healingNum.Value;
            c.skills.knowledge = knowNum.Value;
            c.skills.leadership = leadershipNum.Value;
            c.skills.stealth = stealthNum.Value;

            characterList.Items.Add(c);
            ClearFields();

        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            characterList.Items.Clear();
            ClearFields();
        }

        private void updateCharacterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Character c = new Character();

            c.FistName = firstNTBox.Text;
            c.LastName = lastNTBox.Text;
            c.Age = ageNumberUD.Value;
            c.Races = (CharacterRace)raceCB.SelectedIndex;

            c.skills.bravery = braveryNum.Value;
            c.skills.cheating = cheatingNum.Value;
            c.skills.disguise = disguiseNum.Value;
            c.skills.endurance = enduranceNum.Value;
            c.skills.healing = healingNum.Value;
            c.skills.knowledge = knowNum.Value;
            c.skills.leadership = leadershipNum.Value;
            c.skills.stealth = stealthNum.Value;

            int index = characterList.SelectedIndex;
            characterList.Items.RemoveAt(index);
            characterList.Items.Insert(index, c);
            ClearFields();
        }

        private void removeCharacterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            characterList.Items.RemoveAt(characterList.SelectedIndex);
            ClearFields();
        }

        private void desToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ClearFields();
            characterList.ClearSelected();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var saveFile = new SaveFileDialog();
            saveFile.Filter = "Character Files (*.csv)|*.csv";
            if (saveFile.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                using (var sw = new System.IO.StreamWriter(saveFile.FileName, false))
                    foreach (Character item in characterList.Items)
                    {
                        string file = item.FistName + "," + item.LastName + "," + item.Age + "," + item.Races + "," + item.skills.bravery + "," +
                            item.skills.cheating + "," + item.skills.disguise + "," + item.skills.endurance + "," + item.skills.healing
                            + "," + item.skills.knowledge + "," + item.skills.leadership + "," + item.skills.stealth;
                        sw.Write(file + Environment.NewLine);
                    }
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.myf)|*.myf";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);
                using (var sr = new System.IO.StreamReader(dlg.FileName, false))
                    while (sr.ReadLine() != null)
                    {
                        string line = reader.ReadLine();
                        Character c = new Character();
                        char[] coma = { ',' };

                        string[] data = line.Split(coma);

                        c.FistName = data[0];
                        c.LastName = data[1];
                        c.Age = Convert.ToInt32(data[2]);
                        c.Races = (CharacterRace) Enum.Parse(typeof (CharacterRace), data[3]);
                        c.skills.bravery = Convert.ToInt32(data[4]);
                        c.skills.cheating = Convert.ToInt32(data[5]);
                        c.skills.disguise = Convert.ToInt32(data[6]);
                        c.skills.endurance = Convert.ToInt32(data[7]);
                        c.skills.healing = Convert.ToInt32(data[8]);
                        c.skills.knowledge = Convert.ToInt32(data[9]);
                        c.skills.leadership = Convert.ToInt32(data[10]);
                        c.skills.stealth = Convert.ToInt32(data[11]);


                        characterList.Items.Add(c);
                    }
                reader.Close();
            }
        }
    }
}
