using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace midterm
{
    public partial class Form1 : Form
    {
        List<WayPoints> pointList = new List<WayPoints>();
        ToolWindow tool = null;

        public Form1()
        {
            InitializeComponent();
            ResetFields();
        }

        public void ResetFields()
        {
            groupBox.Visible = false;
            updateToolStripMenuItem.Enabled = false;
            removeToolStripMenuItem.Enabled = false;
            deselectToolStripMenuItem.Enabled = false;
            labelTB.Text = "Default";
            numericX.Value = 0;
            numericY.Value = 0;
        }
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pointList.Clear();
            listBox.Items.Clear();
            ResetFields();
            graphicsPanel1.Invalidate();
        }

        private void graphicsPanel1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                WayPoints mp = new WayPoints();

                mp.IsSelected = false;
                mp.Label = labelTB.Text;
                mp.ValueX = e.X;
                mp.ValueY = e.Y;
                mp.Rec = new Rectangle(e.X -25, e.Y -25, 50, 50);

                pointList.Add(mp);
                listBox.Items.Add(mp);
            }
            else // right button
            {
                for (int i = 0; i < pointList.Count; i++)
                {
                    if (pointList[i].IsSelected == true)
                    {
                        pointList[i].IsSelected = false;
                    }
                }
                for (int i = 0; i < pointList.Count; i++)
                {
                    if (pointList[i].Rec.Contains(e.Location))
                    {
                        pointList[i].IsSelected = true;
                        listBox.SelectedIndex = i;
                        groupBox.Visible = true;
                        updateToolStripMenuItem.Enabled = true;
                        removeToolStripMenuItem.Enabled = true;
                        deselectToolStripMenuItem.Enabled = true;
                        break;
                    }
                }
            }
            graphicsPanel1.Invalidate();
        }

        private void graphicsPanel1_Paint(object sender, PaintEventArgs e)
        {
            Font font = new Font("Times New Roman", 8);
            for (int i = 0; i < pointList.Count; i++)
            {
                if (pointList[i].IsSelected == true)
                {
                    Pen p = new Pen(Color.Red, 7.0f);
                    e.Graphics.DrawRectangle(p, pointList[i].Rec);
                }
                else
                {
                    e.Graphics.DrawRectangle(Pens.Black, pointList[i].Rec);
                }
                Point po = new Point();
                po.X = pointList[i].ValueX;
                po.Y = pointList[i].ValueY;
                e.Graphics.DrawString(pointList[i].Label, font, Brushes.Black, po);
            }

            for (int i = 0; i < pointList.Count - 1; i++)
            {

                Point po1 = new Point(pointList[i].ValueX , pointList[i].ValueY);
                Point po2 = new Point(pointList[i + 1].ValueX , pointList[i + 1].ValueY );
                Pen p = new Pen(Color.Black, 2.0f);

                e.Graphics.DrawLine(p, po1, po2);
            }
        }

        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            groupBox.Visible = true;
            updateToolStripMenuItem.Enabled = true;
            removeToolStripMenuItem.Enabled = true;
            deselectToolStripMenuItem.Enabled = true;

            for (int i = 0; i < pointList.Count; i++)
            {
                if (pointList[i].IsSelected == true)
                {
                    pointList[i].IsSelected = false;
                }
            }
            if (listBox.SelectedIndex != -1)
            {
                labelTB.Text = pointList[listBox.SelectedIndex].Label;
                numericX.Value = pointList[listBox.SelectedIndex].ValueX;
                numericY.Value = pointList[listBox.SelectedIndex].ValueY;
                pointList[listBox.SelectedIndex].IsSelected = true;
            }

            graphicsPanel1.Invalidate();
        }

        private void deselectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < pointList.Count; i++)
            {
                if (pointList[i].IsSelected == true)
                {
                    pointList[i].IsSelected = false;
                }
            }
            listBox.SelectedIndex = -1;
            ResetFields();
        }

        private void removeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < pointList.Count; i++)
            {
                if (pointList[i].IsSelected == true)
                {
                    pointList.Remove(pointList[i]);
                    listBox.Items.RemoveAt(i);
                    break;
                }
            }
            ResetFields();
            graphicsPanel1.Invalidate();
        }

        private void updateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int index = 0;
            for (int i = 0; i < pointList.Count; i++)
            {
                if (pointList[i].IsSelected == true)
                {
                    pointList.Remove(pointList[i]);
                    listBox.Items.RemoveAt(i);
                    index = i;
                    break;
                }
            }

            WayPoints mp = new WayPoints();

            mp.IsSelected = true;
            mp.Label = labelTB.Text;
            mp.ValueX = (int)numericX.Value;
            mp.ValueY = (int)numericY.Value;
            mp.Rec = new Rectangle(mp.ValueX - 25, mp.ValueY - 25, 50, 50);

            pointList.Insert( index, mp);
            listBox.Items.Insert( index, mp);
            graphicsPanel1.Invalidate();
        }

        private void toolsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (tool == null)
            {
                tool = new ToolWindow();

                tool.Owner = this;

                tool.FormClosed += tool_FormClosed;
                tool.ToolWindowUpdateClick += tool_ToolWindowAddClick;

                tool.Show(this);
            }
        }

        void tool_FormClosed(object sender, FormClosedEventArgs e)
        {
            tool = null;
        }

        void tool_ToolWindowAddClick(object sender, EventArgs e)
        {
            labelTB.Text = tool.ToolWindowLabelText;
            numericX.Value = tool.ToolWindowNumericXValue;
            numericY.Value = tool.ToolWindowNumericYValue;

            WayPoints mp = new WayPoints();

            mp.IsSelected = false;
            mp.Label = labelTB.Text;
            mp.ValueX = (int)numericX.Value;
            mp.ValueY = (int)numericY.Value;
            mp.Rec = new Rectangle(mp.ValueX - 25, mp.ValueY - 25, 50, 50);

            pointList.Add(mp);
            listBox.Items.Add(mp);

            groupBox.Visible = true;
            updateToolStripMenuItem.Enabled = true;
            removeToolStripMenuItem.Enabled = true;
            deselectToolStripMenuItem.Enabled = true;

            graphicsPanel1.Invalidate();

        }


    }
}
