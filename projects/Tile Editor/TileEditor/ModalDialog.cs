using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileEditorSkeleton
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
            AcceptButton = OKButton;
            CancelButton = CancelBtt;
        }
        public int mapSizeWidth 
        {
            get
            {
                return (int)mapWidthUD.Value;
            }
            set
            {
                mapWidthUD.Value = (decimal)value;
            }
        }
        public int mapSizeHeight
        {
            get
            {
                return (int)mapHeightUD.Value;
            }
            set
            {
                mapHeightUD.Value = (decimal)value;
            }
        }

        public int tileSetSizeWidth
        {
            get
            {
                return (int)tileSetWidthUD.Value;
            }
            set
            {
                tileSetWidthUD.Value = (decimal)value;
            }
        }
        public int tileSetSizeHeight
        {
            get
            {
                return (int)tileSetHeightUD.Value;
            }
            set
            {
                tileSetHeightUD.Value = (decimal)value;
            }
        }
        Bitmap map;
        public Bitmap myBitmap
        {
            get
            {
                return map;
            }
            set
            {
                map = value;
            }
        }
        public int tileSize
        {
            get
            {
                if (size16RB.Checked == true)
                {
                    return 16;
                }
                if (size32RB.Checked == true)
                {
                    return 32;
                }
                if (size64RB.Checked == true)
                {
                    return 64;
                }
                else
                {
                    return 0;
                }
            }
            set
            {
                if (value == 16)
                {
                    size16RB.Checked = true;
                }
                if (value == 32)
                {
                    size32RB.Checked = true;
                }
                if (value == 64)
                {
                    size64RB.Checked = true;
                }
            }
        }


        private void ApplyButton_Click(object sender, EventArgs e)
        {
             // Publish the event if it is not null
            // and pass the information with the custom 
            // event arguements class. 
            if (Apply != null) Apply(this, new ApplyEventArgs(mapSizeWidth, mapSizeHeight, tileSetSizeWidth, tileSetSizeHeight,myBitmap, tileSize));
    }

        private void importBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.myf)|*.myf";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);

                map = (Bitmap)Image.FromFile(dlg.FileName);


                reader.Close();
            }
            miniMapView.Invalidate();
        }

        private void miniMapView_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = miniMapView.CreateGraphics();
            map.SetResolution(g.DpiX*2, g.DpiY*2);
            g.Dispose();
            e.Graphics.DrawImage(map, new Point(0, 0));
            Point bitmapsXY = new Point(0, 0);
            e.Graphics.DrawImage(map, bitmapsXY);
        }

      

    }
}
