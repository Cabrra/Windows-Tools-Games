using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace tool
{
    public delegate void ApplyEventHandler(object sender, ApplyEventArgs e);

    public partial class ModalDialog : Form
    {
       public event ApplyEventHandler Apply;

        public ModalDialog()
        {
            InitializeComponent();
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MinimizeBox = false;
            MaximizeBox = false;
            StartPosition = FormStartPosition.CenterScreen;
            OKButton.DialogResult = DialogResult.OK;
            CancelBtt.DialogResult = DialogResult.Cancel;
            CancelButton = CancelBtt;
            AcceptButton = OKButton;
        }

        bool position;

        public bool Position
        {
            get
            {
                if (positioncheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (positioncheck.Checked == true)
                {
                    position = true;
                }
                else
                {
                    position = false;
                }
            }
        }

        bool particleInfo;

        public bool ParticleInfo
        {
            get
            {
                if (ParticleInfoCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (ParticleInfoCheck.Checked == true)
                {
                    particleInfo = true;
                }
                else
                {
                    particleInfo = false;
                }
            }
        }

        bool myemitterType;

        public bool EmitterType
        {
            get
            {
                if (EmitterTypeCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (EmitterTypeCheck.Checked == true)
                {
                    myemitterType = true;
                }
                else
                {
                    myemitterType = false;
                }
            }
        }

        bool myemitterInfo;

        public bool EmitterInfo
        {
            get
            {
                if (EmmiterInfoCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (EmmiterInfoCheck.Checked == true)
                {
                    myemitterInfo = true;
                }
                else
                {
                    myemitterInfo = false;
                }
            }
        }

        bool mybasicI;

        public bool BasicInfo
        {
            get
            {
                if (BasicInfoCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (BasicInfoCheck.Checked == true)
                {
                    mybasicI = true;
                }
                else
                {
                    mybasicI = false;
                }
            }
        }

        bool mycolor;

        public bool Color
        {
            get
            {
                if (ColorCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (ColorCheck.Checked == true)
                {
                    mycolor = true;
                }
                else
                {
                    mycolor = false;
                }
            }
        }

        bool myvelX;

        public bool VeloX
        {
            get
            {
                if (VelocityXCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (VelocityXCheck.Checked == true)
                {
                    VeloX = true;
                }
                else
                {
                    VeloX = false;
                }
            }
        }

        bool myvelY;

        public bool VeloY
        {
            get
            {
                if (VelocityYCheck.Checked == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            set
            {
                if (VelocityYCheck.Checked == true)
                {
                    myvelY = true;
                }
                else
                {
                    myvelY = false;
                }
            }
        }


        private void ApplyBtt_Click_1(object sender, EventArgs e)
        {
            // Publish the event if it is not null
            // and pass the information with the custom 
            // event arguements class. 
            if (Apply != null) Apply(this, new ApplyEventArgs(Position, ParticleInfo, EmitterType, EmitterInfo, BasicInfo, Color, VeloX, VeloY));
        }

        private void SelectAllCheck_CheckedChanged(object sender, EventArgs e)
        {
            if (SelectAllCheck.Checked == true)
            {
                positioncheck.Checked = true;
                ParticleInfoCheck.Checked = true;
                EmitterTypeCheck.Checked = true;
                EmmiterInfoCheck.Checked = true;
                BasicInfoCheck.Checked = true;
                ColorCheck.Checked = true;
                VelocityXCheck.Checked = true;
                VelocityYCheck.Checked = true;
            }
            else
            {
                positioncheck.Checked = false;
                ParticleInfoCheck.Checked = false;
                EmitterTypeCheck.Checked = false;
                EmmiterInfoCheck.Checked = false;
                BasicInfoCheck.Checked = false;
                ColorCheck.Checked = false;
                VelocityXCheck.Checked = false;
                VelocityYCheck.Checked = false;
            }
        }

    }
}
