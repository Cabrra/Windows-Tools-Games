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
    public partial class ToolWindow : Form
    {
        public event EventHandler ToolWindowUpdateClick;

        public ToolWindow()
        {
            InitializeComponent();
        }

        public string ToolWindowLabelText
        {
            get
            {
                return labelTB.Text;
            }
            set
            {
                labelTB.Text = value;
            }
        }

        public decimal ToolWindowNumericXValue
        {
            get
            {
                return numericX.Value;
            }
            set
            {
                numericX.Value = value;
            }
        }

        public decimal ToolWindowNumericYValue
        {
            get
            {
                return numericY.Value;
            }
            set
            {
                numericY.Value = value;
            }
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {

            Form1 form1 = (Form1)this.Owner;
            // form1. = numericX.Value;

            if (ToolWindowUpdateClick != null)
            {
                ToolWindowUpdateClick(this, EventArgs.Empty);
            }
        }



    }
}