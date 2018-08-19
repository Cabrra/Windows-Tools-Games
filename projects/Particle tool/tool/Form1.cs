using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;


namespace tool
{
    public partial class Form1 : Form
    {
        bool looping = true;
        SGP.CSGP_Direct3D D3D;
        SGP.CSGP_TextureManager TM;
        List<Particle> lifeLits;
        List<Particle> deadList;
        Random random = new Random();

        bool render = true;

        string particleImage;
        int imageindex;
        DateTime time = System.DateTime.Now;

        ParticleFlyweight myFlyweight;
        Emitter myEmitter;

        double elapsedSpawn = 0;
        float spawnRat;

        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }
        public Form1()
        {
            InitializeComponent();
            EmitterTypeCB.SelectedIndex = 0;

            D3D = SGP.CSGP_Direct3D.GetInstance();
            TM = SGP.CSGP_TextureManager.GetInstance();

            D3D.Initialize(DrawPanel, true);
            D3D.AddRenderTarget(InputPanel);

            TM.Initialize(D3D.Device, D3D.Sprite);

             myFlyweight = new ParticleFlyweight();
             myEmitter = new Emitter();

            //lists

            deadList = new List<Particle>();
            lifeLits = new List<Particle>();
        }

        public new void Update()
        {
            DateTime currentTime = System.DateTime.Now;
            TimeSpan elapsed = currentTime - time;
            time = DateTime.Now;

            if (lifeLits.Count > 0)
            {
                for (int i = 0; i < lifeLits.Count; i++)
                {
                    if (lifeLits[i].CurrentLife <= 0)
                    {
                        deadList.Add(lifeLits[i]);
                        lifeLits.Remove(lifeLits[i]);
                    }
                    else
                    {
                        double myTime = elapsed.TotalSeconds;
                        lifeLits[i].CurrentLife -= (float)myTime;
                        //color
                        Color myCol = Color.FromArgb((int)LerpFunctionColor(myFlyweight.AlphaStart, myFlyweight.AlphaEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original)), //alpha
                           (int)LerpFunctionColor(myFlyweight.RedStart, myFlyweight.RedEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original)), //Red
                            (int)LerpFunctionColor(myFlyweight.GreenStart, myFlyweight.GreenEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original)), //Green
                            (int)LerpFunctionColor(myFlyweight.BlueStart, myFlyweight.BlueEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original)) //Blue
                            );


                        lifeLits[i].CurrentAlpha = myCol.A;
                        lifeLits[i].CurrentRed = myCol.R;
                        lifeLits[i].CurrentGreen = myCol.G;
                        lifeLits[i].CurrentBlue = myCol.B;


                        lifeLits[i].CurrentScale = LerpFunction(myFlyweight.ScaleStart, myFlyweight.ScaleEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original));
                        lifeLits[i].CurrentRotation = LerpFunction(myFlyweight.RotationStart, myFlyweight.RotationEnd, 1 - (lifeLits[i].CurrentLife / lifeLits[i].Original));
                        lifeLits[i].CurrentVelocityX = lifeLits[i].CurrentVelocityX + lifeLits[i].ChangeVelocityX * ((float)myTime);
                        lifeLits[i].CurrentVelocityY = lifeLits[i].CurrentVelocityY + lifeLits[i].ChangeVelocityY * ((float)myTime);
                    
                        //position
                        lifeLits[i].CurrentPositionX = lifeLits[i].CurrentPositionX + lifeLits[i].CurrentVelocityX * ((float)myTime);
                        lifeLits[i].CurrentPositionY = lifeLits[i].CurrentPositionY + lifeLits[i].CurrentVelocityY * ((float)myTime);
                    }
                }
            }

            if (elapsedSpawn > spawnRat && deadList.Count > 0)
            {
                if (CheckFields())
                {
                    if (FirstWaveUD.Value > 0)
                        for (decimal wave = 0; wave < FirstWaveUD.Value; wave++)
                        {
                            if (deadList.Count > 0)
                                SpawnParticle();
                            else
                                break;
                        }
                    else
                        SpawnParticle();
                    elapsedSpawn = 0;
                }
            }
            else
                elapsedSpawn += elapsed.TotalSeconds;
        }

        public void Render()
        {


            D3D.Clear(DrawPanel, Color.Black);

            D3D.DeviceBegin();
            D3D.SpriteBegin();

            if (CheckFields())
            {
                for (int i = 0; i < lifeLits.Count; i++)
                {
                    Rectangle rect = new Rectangle(
                     0,
                     0,
                     TM.GetTextureWidth(imageindex),
                     TM.GetTextureHeight(imageindex)
                    );

                    Color col = Color.FromArgb((int)lifeLits[i].CurrentAlpha, (int)lifeLits[i].CurrentRed,
                        (int)lifeLits[i].CurrentGreen, (int)lifeLits[i].CurrentBlue);

                    SGP.CSGP_TextureManager.GetInstance().Draw(imageindex, (int)lifeLits[i].CurrentPositionX, (int)lifeLits[i].CurrentPositionY, lifeLits[i].CurrentScale,
                        lifeLits[i].CurrentScale, rect, (float)(TM.GetTextureWidth(imageindex)*lifeLits[i].CurrentScale) / 2, (float)(TM.GetTextureHeight(imageindex)*lifeLits[i].CurrentScale) / 2, lifeLits[i].CurrentRotation, col);
                }
            }

            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();

            D3D.Clear(InputPanel, Color.White);
            D3D.DeviceBegin();
            D3D.SpriteBegin();

            D3D.SpriteEnd();
            D3D.DeviceEnd();
            D3D.Present();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            looping = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void LoadImageButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Image Files ( JPEG,BMP,PNG )|*.jpg;*.jpeg;*.bmp;*.png;|JPEG Files ( *.jpg;*.jpeg )|*.jpg;*.jpeg|BMP Files ( *.bmp )|*.bmp|PNG Files ( *.png )|*.png| All Files (*.*)|*.*";

            if (DialogResult.OK == dlg.ShowDialog())
            {

                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);

                if (particleImage != null)
                    TM.UnloadTexture(imageindex);

                particleImage = dlg.FileName;
                ImagePathTextBox.Text = dlg.SafeFileName;

                reader.Close();
            }

            imageindex = TM.LoadTexture(particleImage);

        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Image Files ( JPEG,BMP,PNG )|*.jpg;*.jpeg;*.bmp;*.png;|JPEG Files ( *.jpg;*.jpeg )|*.jpg;*.jpeg|BMP Files ( *.bmp )|*.bmp|PNG Files ( *.png )|*.png| All Files (*.*)|*.*";

            if (DialogResult.OK == dlg.ShowDialog())
            {

                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);

                if (particleImage != null)
                    TM.UnloadTexture(imageindex);

                particleImage = dlg.FileName;
                ImagePathTextBox.Text = dlg.SafeFileName;

                reader.Close();
            }

            imageindex = TM.LoadTexture(particleImage);
        }

        private void MaxParticlesUD_ValueChanged(object sender, EventArgs e)
        {
            if (lifeLits != null)
                lifeLits.Clear();
            if (deadList != null)
                deadList.Clear();

            myEmitter.MaxParticles = (float)MaxParticlesUD.Value;
            for (decimal i = 0; i < MaxParticlesUD.Value; i++)
            {
                Particle newPart = new Particle();
                deadList.Add(newPart);
            }
        }

        private bool CheckFields()
        {
            if (MaxLifeUD.Value == 0)
                return false;
            if (ScaleStartUD.Value == 0 && ScaleEndUD.Value == 0)
                return false;
            if (ImagePathTextBox.Text == "")
                return false;
            if (render == false)
                return false;
            if (VelocityMinStartX.Value > VelocityMaxStartX.Value)
                return false;
            if (VelocityMinEndX.Value > VelocityEndMaxX.Value)
                return false;
            if (VelocityMinStartY.Value > VelocityMaxStartY.Value)
                return false;
            if (VelocityMinEndY.Value > VelocityMaxEndY.Value)
                return false;
            if (MaxLifeUD.Value < MinLifeUD.Value)
                return false;

            return true;
        }

        private void SpawnParticle()
        {
            if (myFlyweight.MinLife < myFlyweight.MaxLife)
            {
                Particle part = deadList[0];

                //current life

                int min = Convert.ToInt32(myFlyweight.MinLife * 100);
                int max = Convert.ToInt32(myFlyweight.MaxLife * 100);
                float current = Convert.ToSingle(random.Next(min, max) / 100);
                part.CurrentLife = current;

                part.Original = current;

                int width = TM.GetTextureWidth(imageindex);
                int height = TM.GetTextureHeight(imageindex);

                //position
                float posX;
                float posY;

                switch (EmitterTypeCB.SelectedIndex)
                {
                    case(1): //line
                        {
                            PointF one = new PointF();
                            PointF two = new PointF();
                            PointF three = new PointF();

                            float slopeX;
                            float slopeY;

                            if (myEmitter.EmitterPositionX == (float)WidthUD.Value)
                            {
                                slopeX = 0.0f;
                                slopeY = 1.0f;
                            }
                            else if (myEmitter.EmitterPositionY == (float)HeightUD.Value)
                            {
                                slopeY = 0.0f;
                                slopeX = 1.0f;
                            }
                            else
                                slopeX = slopeY = Math.Abs((float)((myEmitter.EmitterPositionY - (float)HeightUD.Value) / (myEmitter.EmitterPositionX - (float)WidthUD.Value)));

                             float length;
                             length = (float)Math.Sqrt( ( ((float)PositionXUD.Value - (float)WidthUD.Value) * ((float)PositionXUD.Value - (float)WidthUD.Value)  + ((float)PositionYUD.Value - (float)HeightUD.Value) * ((float)PositionYUD.Value - (float)HeightUD.Value) ));


                             if (slopeX == 0 || slopeY == 0)
                            {
                                posX = random.Next((int)((float)PositionXUD.Value - 1 - ((length / 2) * slopeX)), (int)((float)PositionXUD.Value + ((length / 2) * slopeX)));
                                posY = random.Next((int)((float)PositionYUD.Value - 1 - ((length / 2) * slopeY)), (int)((float)PositionYUD.Value + ((length / 2) * slopeY)));

                                part.CurrentPositionX = posX;
                                part.CurrentPositionY = posY;
                            }
                            else if (slopeX != 0 && slopeY != 0)
                            {
                               
                                  do
                                  {
                                      posX = random.Next((int)((float)PositionXUD.Value - 1 - ((length/2) * slopeX)), (int)((float)PositionXUD.Value + ((length/2) * slopeX)));
                                      posY = random.Next((int)((float)PositionYUD.Value - 1 - ((length/2) * slopeY)), (int)((float)PositionYUD.Value + ((length/2) * slopeY)));

                                      part.CurrentPositionX = posX;
                                      part.CurrentPositionY = posY;

                                      one.X = myEmitter.EmitterPositionX;
                                      one.Y = myEmitter.EmitterPositionY;

                                      two.X = (float)WidthUD.Value;
                                      two.Y = (float)HeightUD.Value;
 
                                      three.X = posX;
                                      three.Y = posY;


                                      if ( IsOnLine(one, two, three) == true) // not in line
                                          break;
                                      if (IsOnLine(one, two, three) == false) // is on line
                                          continue;
                                      

                                  } while (true);


                                  part.CurrentPositionX = posX;
                                  part.CurrentPositionY = posY;
                            }

                           
                            break;
                        }
                    case (2): //Rectangle
                        {
                            posX = random.Next((int)(PositionXUD.Value - WidthUD.Value), (int)(PositionXUD.Value + WidthUD.Value));
                            part.CurrentPositionX = posX;

                            posY = random.Next((int)(PositionXUD.Value - HeightUD.Value), (int)(PositionXUD.Value + HeightUD.Value));
                            part.CurrentPositionY = posY;

                            render = true;

                            break;
                        }
                    case (3): //Circle
                        {
                            float distance;
                            do
                            {
                                posX = random.Next((int)(PositionXUD.Value - WidthUD.Value), (int)(PositionXUD.Value + WidthUD.Value));
                                part.CurrentPositionX = posX;

                                posY = random.Next((int)(PositionYUD.Value - WidthUD.Value), (int)(PositionYUD.Value + WidthUD.Value));
                                part.CurrentPositionY = posY;
                                distance = (float)Math.Sqrt((Math.Pow(posX - (float)PositionXUD.Value, 2.0f ) + Math.Pow(posY - (float)PositionYUD.Value, 2.0f)));

                                //(x - center_x)^2 + (y - center_y)^2 < radius^2.
                            } while (distance > (float)WidthUD.Value);
                            render = true;
                            break;
                        }
                    case (4): //Cone
                        {
                            float distance;

                            PointF one = new PointF();
                            PointF two = new PointF();
                            PointF three = new PointF();
                            PointF check = new PointF();


                            do
                            {
                                posX = random.Next((int)(PositionXUD.Value - WidthUD.Value), (int)(PositionXUD.Value + WidthUD.Value));
                                posY = random.Next((int)(PositionYUD.Value - WidthUD.Value), (int)(PositionYUD.Value + WidthUD.Value));

                                distance = (float)Math.Sqrt(((((float)CenterXUD.Value - posX)) + ( ((float)CenterYUD.Value - posY))));

                                check.X = posX;
                                check.Y = posY;

                                one.X = (float)PositionXUD.Value;
                                one.Y = (float)PositionYUD.Value;

                                two.X = (float)(CenterXUD.Value + WidthUD.Value);
                                two.Y = (float)CenterYUD.Value;

                                three.X = (float)(CenterXUD.Value - WidthUD.Value);
                                three.Y = (float)CenterYUD.Value;

                            } while (distance < (float)WidthUD.Value && IsInTriangle(check, one, two, three));

                            part.CurrentPositionX = posX;
                            part.CurrentPositionY = posY;

                            break;
                        }

                    default: //Point
                        {
                            posX = random.Next((int)(PositionXUD.Value) , (int)(PositionXUD.Value) );
                            posY = random.Next((int)(PositionXUD.Value), (int)(PositionXUD.Value));
                            //posX = ((Convert.ToSingle(PositionXUD.Value) - (width / 2) * myFlyweight.ScaleStart)) + random.Next((int)(((Convert.ToSingle(PositionXUD.Value) - (width / 2) * myFlyweight.ScaleStart)) - (Convert.ToSingle(PositionXUD.Value) - (width / 2) * myFlyweight.ScaleStart) ));
                           // posY = ((Convert.ToSingle(PositionYUD.Value) - (height / 2) * myFlyweight.ScaleStart)) + random.Next((int)(((Convert.ToSingle(PositionYUD.Value) - (height / 2) * myFlyweight.ScaleStart)) - (Convert.ToSingle(PositionYUD.Value) - (height / 2) * myFlyweight.ScaleStart) ));
                            part.CurrentPositionX = posX;
                            part.CurrentPositionY = posY;

                            render = true;
                            break;
                        }

                }

                //color
                part.CurrentAlpha = myFlyweight.AlphaStart;
                part.CurrentRed = myFlyweight.RedStart;
                part.CurrentGreen = myFlyweight.GreenStart;
                part.CurrentBlue = myFlyweight.BlueStart;

                part.CurrentScale = myFlyweight.ScaleStart;

                float velX;
                if (myFlyweight.VelStartMinX == 0 || myFlyweight.VelStartMaxX == 0)
                    velX = 0.0f;
                else
                    velX = (myFlyweight.VelStartMinX + random.Next(Convert.ToInt32(myFlyweight.VelStartMaxX * 100) - Convert.ToInt32(myFlyweight.VelStartMinX * 100)) / 100);

                part.CurrentVelocityX = velX;

                float velY;
                if (myFlyweight.VelStartMinY == 0 || myFlyweight.VelStartMaxY == 0)
                    velY = 0.0f;
                else
                    velY = (myFlyweight.VelStartMinY + random.Next(Convert.ToInt32(myFlyweight.VelStartMaxY * 100) - Convert.ToInt32(myFlyweight.VelStartMinY * 100)) / 100);

                part.CurrentVelocityY = velY;

                //calculate  velocity ratios
                ChangeRatioCalculator(deadList[0]);
                lifeLits.Add(deadList[0]);
                deadList.Remove(deadList[0]);
            }
        }

        private void ChangeRatioCalculator(Particle part)
        {

            float CvelX;
            if (myFlyweight.VelEndMinX == 0 || myFlyweight.VelEndMinX == 0 || myFlyweight.VelEndMinX  > myFlyweight.VelEndMaxX )
                CvelX = 0;
            else
                CvelX = (random.Next(Convert.ToInt32(myFlyweight.VelEndMinX * 100), Convert.ToInt32(myFlyweight.VelEndMaxX * 100)) / 100) / part.CurrentLife;

            part.ChangeVelocityX = CvelX;

            float CvelY;
            if (myFlyweight.VelEndMinY == 0 || myFlyweight.VelEndMaxY == 0 || myFlyweight.VelEndMinY > myFlyweight.VelEndMaxY)
                CvelY = 0;
            else
                CvelY = ( random.Next(Convert.ToInt32(myFlyweight.VelEndMaxY * 100), Convert.ToInt32(myFlyweight.VelEndMaxY * 100)) / 100) / part.CurrentLife;

            part.ChangeVelocityY = CvelY;

        }

        private void SpawnRateUD_ValueChanged(object sender, EventArgs e)
        {
            spawnRat = (float)SpawnRateUD.Value;
            myEmitter.SpawnRate = (float)SpawnRateUD.Value;
        }

        private void MaxLifeUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.MaxLife = (float)MaxLifeUD.Value;
        }

        private void MinLifeUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.MinLife = (float)MinLifeUD.Value;
            if (MinLifeUD.Value > MaxLifeUD.Value)
                MaxLifeUD.Value = MinLifeUD.Value;
        }

        private void RotationStartUD_ValueChanged(object sender, EventArgs e)
        {
            float angle = (float)RotationStartUD.Value;
            angle = (float)(angle * Math.PI) / 180;
            myFlyweight.RotationStart = angle;
        }

        private void RotationEndUD_ValueChanged(object sender, EventArgs e)
        {
            float angle = (float)RotationEndUD.Value;
            angle = (float)(angle * Math.PI) / 180;
            myFlyweight.RotationEnd = angle;
        }

        private void ScaleStartUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.ScaleStart = (float)ScaleStartUD.Value;
        }

        private void ScaleEndUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.ScaleEnd = (float)ScaleEndUD.Value;
        }

        private void AlphaStartUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.AlphaStart = (float)AlphaStartUD.Value;
        }

        private void RedStartUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.RedStart = (float)RedStartUD.Value;
        }

        private void GreenStartUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.GreenStart = (float)GreenStartUD.Value;
        }

        private void BlueStartUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.BlueStart = (float)BlueStartUD.Value;
        }

        private void AlphaEndUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.AlphaEnd = (float)AlphaEndUD.Value;
        }

        private void RedEndUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.RedEnd = (float)RedEndUD.Value;
        }

        private void GreenEndUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.GreenEnd = (float)GreenEndUD.Value;
        }

        private void BlueEndUD_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.BlueEnd = (float)BlueEndUD.Value;
        }

        private void VelocityMinStartX_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelStartMinX = (float)VelocityMinStartX.Value;
        }

        private void VelocityMaxStartX_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelStartMaxX = (float)VelocityMaxStartX.Value;
        }

        private void VelocityMinEndX_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelEndMinX = (float)VelocityMinEndX.Value;
        }

        private void VelocityEndMaxX_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelEndMaxX = (float)VelocityEndMaxX.Value;
        }

        private void VelocityMinStartY_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelStartMinY = (float)VelocityMinStartY.Value;
        }

        private void VelocityMaxStartY_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelStartMaxY = (float)VelocityMaxStartY.Value;
        }

        private void VelocityMinEndY_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelEndMinY = (float)VelocityMinEndY.Value;
        }

        private void VelocityMaxEndY_ValueChanged(object sender, EventArgs e)
        {
            myFlyweight.VelEndMaxY = (float)VelocityMaxEndY.Value;
        }

        private void WidthUD_ValueChanged(object sender, EventArgs e)
        {
            myEmitter.EmitterWidth = (float)WidthUD.Value;
        }

        private void HeightUD_ValueChanged(object sender, EventArgs e)
        {
            myEmitter.EmitterHeight = (float)HeightUD.Value;
        }

        private void PositionXUD_ValueChanged(object sender, EventArgs e)
        {;
            if (EmitterTypeCB.SelectedIndex == 1 && PositionXUD.Value < WidthUD.Value && PositionXUD.Value < 50)
                PositionXUD.Value = 50;
            myEmitter.EmitterPositionX = (float)PositionXUD.Value;
        }

        private void PositionYUD_ValueChanged(object sender, EventArgs e)
        {
            if (EmitterTypeCB.SelectedIndex == 1 && PositionYUD.Value < HeightUD.Value && PositionYUD.Value < 50)
                PositionYUD.Value = 50;
            myEmitter.EmitterPositionY = (float)PositionYUD.Value;
        }

        private void FirstWaveUD_ValueChanged(object sender, EventArgs e)
        {
            myEmitter.FirstWave = (float)FirstWaveUD.Value;
        }

        private void StartColorButton_Click(object sender, EventArgs e)
        {
            ColorDialog colorDlg = new ColorDialog();

            colorDlg.AllowFullOpen = true;
            colorDlg.AnyColor = true;
            colorDlg.SolidColorOnly = false;
            colorDlg.Color = Color.Red;

            if (colorDlg.ShowDialog() == DialogResult.OK)
            {
                System.Drawing.Color col = colorDlg.Color;
                AlphaStartUD.Value = Convert.ToDecimal(col.A);
                RedStartUD.Value = Convert.ToDecimal(col.R);
                GreenStartUD.Value = Convert.ToDecimal(col.G);
                BlueStartUD.Value = Convert.ToDecimal(col.B);

            }
        }

        private void EndColorButton_Click(object sender, EventArgs e)
        {

            ColorDialog colorDlg = new ColorDialog();

            colorDlg.AllowFullOpen = true;
            colorDlg.AnyColor = true;
            colorDlg.SolidColorOnly = false;

            if (colorDlg.ShowDialog() == DialogResult.OK)
            {
                System.Drawing.Color col = colorDlg.Color;
                AlphaEndUD.Value = Convert.ToDecimal(col.A);
                RedEndUD.Value = Convert.ToDecimal(col.R);
                GreenEndUD.Value = Convert.ToDecimal(col.G);
                BlueEndUD.Value = Convert.ToDecimal(col.B);

            }
        }

        private void EmitterTypeCB_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (EmitterTypeCB.SelectedIndex == 0) //point
            {
                EmitterTypeGroupBox.Visible = false;
                EmitterTypeGroupBox.Enabled = false;
            }

            else if (EmitterTypeCB.SelectedIndex == 1) //line
            {
                EmitterTypeWidthLabel.Text = "Point2 X";
                EmitterTypeHeightLabel.Text = "Point2 Y";

                EmitterTypeGroupBox.Visible = true;
                EmitterTypeGroupBox.Enabled = true;

                EmitterTypeHeightLabel.Visible = true;
                HeightUD.Visible = true;

                CenterGB.Visible = false;
                CenterGB.Enabled = false;
            }

            else if (EmitterTypeCB.SelectedIndex == 2) //rectangle
            {
                EmitterTypeWidthLabel.Text = "Width";
                EmitterTypeHeightLabel.Text = "Height";

                EmitterTypeHeightLabel.Visible = true;
                HeightUD.Visible = true;

                EmitterTypeGroupBox.Visible = true;
                EmitterTypeGroupBox.Enabled = true;
            }

            else if(EmitterTypeCB.SelectedIndex == 3) //circle
            {
                EmitterTypeWidthLabel.Text = "Radius";
               
                EmitterTypeGroupBox.Visible = true;
                EmitterTypeGroupBox.Enabled = true;

                HeightUD.Visible = false;
                EmitterTypeHeightLabel.Visible = false;

                CenterGB.Visible = false;
                CenterGB.Enabled = false;

            }

            else if (EmitterTypeCB.SelectedIndex == 4) //cone
            {
                EmitterTypeWidthLabel.Text = "Radius";
                EmitterTypeHeightLabel.Visible = false;
                HeightUD.Visible = false;

                CenterGB.Visible = true;
                CenterGB.Enabled = true;

                EmitterTypeGroupBox.Visible = true;
                EmitterTypeGroupBox.Enabled = true;
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SpawnRateUD.Value = 0;
            MaxLifeUD.Value = 0;
            MinLifeUD.Value = 0;
            RotationStartUD.Value = 0;
            RotationEndUD.Value = 0;
            ScaleStartUD.Value = 0;
            ScaleEndUD.Value = 0;
            AlphaStartUD.Value = 0;
            RedStartUD.Value = 0;
            GreenStartUD.Value = 0;
            BlueStartUD.Value = 0;
            AlphaEndUD.Value = 0;
            RedEndUD.Value = 0;
            GreenEndUD.Value = 0;
            BlueEndUD.Value = 0;
            VelocityMinStartX.Value = 0;
            VelocityMaxStartX.Value = 0;
            VelocityMinEndX.Value = 0;
            VelocityEndMaxX.Value = 0;
            VelocityMinStartY.Value = 0;
            VelocityMaxStartY.Value = 0;
            VelocityMinEndY.Value = 0;
            VelocityMaxEndY.Value = 0;
            EmitterTypeCB.SelectedIndex = 0;
            PositionXUD.Value = 0;
            PositionYUD.Value = 0;
            FirstWaveUD.Value = 0;
            MaxParticlesUD.Value = 0;
        }

        private void randomizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ModalDialog dlg = new ModalDialog();

            dlg.Apply += new ApplyEventHandler(dlg_Apply);
            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (dlg.Position == true)
                {
                    PositionXUD.Value = random.Next(999);
                    PositionYUD.Value = random.Next(999);
                }

                if (dlg.ParticleInfo == true)
                {
                    SpawnRateUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);

                    MaxParticlesUD.Value = random.Next(1200);
                    do
                    {
                        FirstWaveUD.Value = random.Next(999);
                    } while (MaxParticlesUD.Value < FirstWaveUD.Value);
                }

                if (dlg.EmitterType == true)
                {
                    EmitterTypeCB.SelectedIndex = random.Next(4); // 4 is cone
                }

                if (dlg.EmitterInfo == true)
                {
                    WidthUD.Value = random.Next(1000);
                    HeightUD.Value = random.Next(1000);

                    CenterXUD.Value = random.Next(1200);
                    CenterYUD.Value = random.Next(1000);
                }

                if (dlg.BasicInfo == true)
                {
                    MinLifeUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);
                    MaxLifeUD.Value = random.Next(10);
                    MaxLifeUD.Value += Convert.ToDecimal((double)random.Next(999) / 1000);
                    
                    RotationStartUD.Value = random.Next(-360, 360);
                    RotationStartUD.Value += Convert.ToDecimal((double)(999)/1000);
                    
                    RotationEndUD.Value = random.Next(-360, 360);
                    RotationEndUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);

                    ScaleStartUD.Value = random.Next(5);
                    ScaleStartUD.Value += Convert.ToDecimal((double)(999) / 1000);
                    ScaleEndUD.Value = random.Next(5);
                    ScaleEndUD.Value += Convert.ToDecimal((double)(999) / 1000);
                }

                if (dlg.Color == true)
                {
                    AlphaStartUD.Value = random.Next(255);
                    RedStartUD.Value = random.Next(255);
                    GreenStartUD.Value = random.Next(255);
                    BlueStartUD.Value = random.Next(255);

                    AlphaEndUD.Value = random.Next(255);
                    RedEndUD.Value = random.Next(255);
                    GreenEndUD.Value = random.Next(255);
                    BlueEndUD.Value = random.Next(255);
                }

                if (dlg.VeloX == true)
                {
                    //velocity
                    VelocityMinStartX.Value = random.Next(-100, 100);
                    VelocityMinStartX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                    do
                    {
                        VelocityMaxStartX.Value = random.Next(-100, 100);
                        VelocityMaxStartX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                    } while (VelocityMaxStartX.Value < VelocityMinStartX.Value);

                    VelocityMinEndX.Value = random.Next(-100, 100);
                    VelocityMinEndX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);

                    do
                    {
                        VelocityEndMaxX.Value = random.Next(-100, 100);
                        VelocityEndMaxX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                    } while (VelocityEndMaxX.Value < VelocityMinEndX.Value);
                }

                if (dlg.VeloY == true)
                {

                    VelocityMinEndY.Value = random.Next(-100, 100);
                    VelocityMinEndY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);

                    VelocityMinStartY.Value = random.Next(-100, 100);
                    VelocityMinStartY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);


                    do
                    {
                        VelocityMaxStartY.Value = random.Next(-100, 100);
                        VelocityMaxStartY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                    } while (VelocityMaxStartY.Value < VelocityMinStartY.Value);

                    do
                    {
                        VelocityMaxEndY.Value = random.Next(-100, 100);
                        VelocityMaxEndY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                    } while (VelocityMaxEndY.Value < VelocityMinEndY.Value);
                }

            }
        }

        void dlg_Apply(object sender, ApplyEventArgs e)
        {
            if (e.PositionChec == true)
            {
                PositionXUD.Value = random.Next(999);
                PositionYUD.Value = random.Next(999);
            }

            if (e.ParticleInfoChec == true)
            {
                SpawnRateUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);

                MaxParticlesUD.Value = random.Next(1200);
                do
                {
                    FirstWaveUD.Value = random.Next(999);
                } while (MaxParticlesUD.Value < FirstWaveUD.Value);
            }

            if (e.EmitterTypeChec == true)
            {
                EmitterTypeCB.SelectedIndex = random.Next(4); // 4 is cone
            }

            if (e.EmitterInfoChec == true)
            {
                WidthUD.Value = random.Next(1000);
                HeightUD.Value = random.Next(1000);

                CenterXUD.Value = random.Next(1200);
                CenterYUD.Value = random.Next(1000);
            }

            if (e.BasicInfoChec == true)
            {
                MinLifeUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);
                MaxLifeUD.Value = random.Next(10);
                MaxLifeUD.Value += Convert.ToDecimal((double)random.Next(999) / 1000);

                RotationStartUD.Value = random.Next(-360, 360);
                RotationStartUD.Value += Convert.ToDecimal((double)(999) / 1000);

                RotationEndUD.Value = random.Next(-360, 360);
                RotationEndUD.Value = Convert.ToDecimal((double)random.Next(999) / 1000);

                ScaleStartUD.Value = random.Next(5);
                ScaleStartUD.Value += Convert.ToDecimal((double)(999) / 1000);
                ScaleEndUD.Value = random.Next(5);
                ScaleEndUD.Value += Convert.ToDecimal((double)(999) / 1000);
            }

            if (e.ColorChec == true)
            {
                AlphaStartUD.Value = random.Next(255);
                RedStartUD.Value = random.Next(255);
                GreenStartUD.Value = random.Next(255);
                BlueStartUD.Value = random.Next(255);

                AlphaEndUD.Value = random.Next(255);
                RedEndUD.Value = random.Next(255);
                GreenEndUD.Value = random.Next(255);
                BlueEndUD.Value = random.Next(255);
            }

            if (e.VeloXChec == true)
            {
                //velocity
                VelocityMinStartX.Value = random.Next(-100, 100);
                VelocityMinStartX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                do
                {
                    VelocityMaxStartX.Value = random.Next(-100, 100);
                    VelocityMaxStartX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                } while (VelocityMaxStartX.Value < VelocityMinStartX.Value);

                VelocityMinEndX.Value = random.Next(-100, 100);
                VelocityMinEndX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);

                do
                {
                    VelocityEndMaxX.Value = random.Next(-100, 100);
                    VelocityEndMaxX.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                } while (VelocityEndMaxX.Value < VelocityMinEndX.Value);
            }

            if (e.VeloYChec == true)
            {

                VelocityMinEndY.Value = random.Next(-100, 100);
                VelocityMinEndY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);

                VelocityMinStartY.Value = random.Next(-100, 100);
                VelocityMinStartY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);


                do
                {
                    VelocityMaxStartY.Value = random.Next(-100, 100);
                    VelocityMaxStartY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                } while (VelocityMaxStartY.Value < VelocityMinStartY.Value);

                do
                {
                    VelocityMaxEndY.Value = random.Next(-100, 100);
                    VelocityMaxEndY.Value += Convert.ToDecimal((double)random.Next(-999, 999) / 1000);
                } while (VelocityMaxEndY.Value < VelocityMinEndY.Value);
            }
        }

        private float LerpFunction(float start, float end, float ratio) 
        {
            float aux = (end - start )* ratio + start;

            return aux;
        }

        private float LerpFunctionColor(float start, float end, float ratio)
        {
            float aux = (end - start) * ratio + start;

            if (aux > 255)
                aux = 255;
            if (aux < 0)
                aux = 0;

            return aux;
        }

        private bool IsInTriangle(PointF checkPoint, PointF vertex1, PointF vertex2, PointF vertex3)
        {
            bool b1, b2, b3;

            b1 = sign(checkPoint, vertex1, vertex2) < 0.0f;
            b2 = sign(checkPoint, vertex2, vertex3) < 0.0f;
            b3 = sign(checkPoint, vertex3, vertex1) < 0.0f;

            return ((b1 == b2) && (b2 == b3));
        }

       private float sign(PointF p1, PointF p2, PointF p3)
        {
            return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
        }

       private void saveToolStripMenuItem_Click(object sender, EventArgs e)
       {
           SaveFileDialog dlg = new SaveFileDialog();

           dlg.Filter = "All Files|*.*|Xml Files|*.xml";
           dlg.FilterIndex = 2;
           dlg.DefaultExt = "xml";

           if (DialogResult.OK == dlg.ShowDialog())
           {
               XElement xRoot = new XElement("Particle_Info");

               XElement myElement = new XElement("Emiter");
               xRoot.Add(myElement);

               XElement subElement = new XElement("Path");
               myElement.Add(subElement);

               XAttribute xValue = new XAttribute("Value", ImagePathTextBox.Text);
               subElement.Add(xValue);

               subElement = new XElement("Width");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", WidthUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("Height");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", HeightUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("PositionX");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", PositionXUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("PositionY");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", PositionYUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ImageSizeWidh");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", TM.GetTextureWidth(imageindex).ToString());
               subElement.Add(xValue);

               subElement = new XElement("ImageSizeHeight");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", TM.GetTextureHeight(imageindex).ToString());
               subElement.Add(xValue);

               subElement = new XElement("MaxParticles");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", MaxParticlesUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("FirstWave");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", FirstWaveUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("SpawnRate");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", SpawnRateUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("Shape");
               myElement.Add(subElement);

               xValue = new XAttribute("Value", EmitterTypeCB.SelectedIndex.ToString());
               subElement.Add(xValue);

               XElement subTree = new XElement("Flyweight");
               myElement.Add(subTree);

               subElement = new XElement("MinLife");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", MinLifeUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("MaxLife");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", MaxLifeUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorStartA");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", AlphaStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorStartR");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", RedStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorStartG");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", GreenStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorStartB");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", BlueStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorEndA");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", AlphaEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorEndR");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", RedEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorEndG");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", GreenEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ColorEndB");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", BlueEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ScaleStart");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", ScaleStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("ScaleEnd");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", ScaleEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("RotationStart");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", RotationStartUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("RotationEnd");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", RotationEndUD.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityStartMinX");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMinStartX.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityStartMaxX");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMaxStartX.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityStartMinY");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMinEndX.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityStartMaxY");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityEndMaxX.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityEndMinX");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMinStartY.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityEndMaxX");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMaxStartY.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityEndMinY");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMinEndY.Value.ToString());
               subElement.Add(xValue);

               subElement = new XElement("VelocityEndMaxY");
               subTree.Add(subElement);

               xValue = new XAttribute("Value", VelocityMaxEndY.Value.ToString());
               subElement.Add(xValue);

               xRoot.Save(dlg.FileName);
           }
       }

       private void opemToolStripMenuItem_Click(object sender, EventArgs e)
       {
           OpenFileDialog dlg = new OpenFileDialog();
           dlg.Filter = "All Files|*.*|Xml Files|*.xml";
           dlg.FilterIndex = 2;

           if (DialogResult.OK == dlg.ShowDialog())
           {
               XElement xRoot = XElement.Load(dlg.FileName);

               XElement mainCont = xRoot.Element("Emiter");

               //XElement myElement = mainCont.Element("RelativePath");
               //XAttribute xVal = myElement.Attribute("Value");
               //String myPath = xVal.Value;

               //if (myPath.Length > 0)
               //{
               //    if (particleImage != null)
               //        TM.UnloadTexture(imageindex);
               //    particleImage = myPath;
               //    imageindex = TM.LoadTexture(particleImage);
               //}

               XElement myElement = mainCont.Element("Path");
               XAttribute xVal = myElement.Attribute("Value");
               ImagePathTextBox.Text = xVal.Value;

               myElement = mainCont.Element("Width");
               xVal = myElement.Attribute("Value");
               WidthUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("Height");
               xVal = myElement.Attribute("Value");
               HeightUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("PositionX");
               xVal = myElement.Attribute("Value");
               PositionXUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("PositionY");
               xVal = myElement.Attribute("Value");
               PositionYUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("MaxParticles");
               xVal = myElement.Attribute("Value");
               MaxParticlesUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("FirstWave");
               xVal = myElement.Attribute("Value");
               FirstWaveUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = mainCont.Element("SpawnRate");
               xVal = myElement.Attribute("Value");
               SpawnRateUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = mainCont.Element("Shape");
               xVal = myElement.Attribute("Value");
               EmitterTypeCB.SelectedIndex = int.Parse(xVal.Value);

               XElement subTree = mainCont.Element("Flyweight");

               myElement = subTree.Element("MinLife");
               xVal = myElement.Attribute("Value");
               MinLifeUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("MaxLife");
               xVal = myElement.Attribute("Value");
               MaxLifeUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("ColorStartA");
               xVal = myElement.Attribute("Value");
               AlphaStartUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorStartR");
               xVal = myElement.Attribute("Value");
               RedStartUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorStartG");
               xVal = myElement.Attribute("Value");
               GreenStartUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorStartB");
               xVal = myElement.Attribute("Value");
               BlueStartUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorEndA");
               xVal = myElement.Attribute("Value");
               AlphaEndUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorEndR");
               xVal = myElement.Attribute("Value");
               RedEndUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorEndG");
               xVal = myElement.Attribute("Value");
               GreenEndUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ColorEndB");
               xVal = myElement.Attribute("Value");
               BlueEndUD.Value = Convert.ToDecimal(int.Parse(xVal.Value));

               myElement = subTree.Element("ScaleStart");
               xVal = myElement.Attribute("Value");
               ScaleStartUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("ScaleEnd");
               xVal = myElement.Attribute("Value");
               ScaleEndUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("RotationStart");
               xVal = myElement.Attribute("Value");
               RotationStartUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("RotationEnd");
               xVal = myElement.Attribute("Value");
               RotationEndUD.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityStartMinX");
               xVal = myElement.Attribute("Value");
               VelocityMinStartX.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityStartMaxX");
               xVal = myElement.Attribute("Value");
               VelocityMaxStartX.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityStartMinY");
               xVal = myElement.Attribute("Value");
               VelocityMinEndX.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityStartMaxY");
               xVal = myElement.Attribute("Value");
               VelocityEndMaxX.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityEndMinX");
               xVal = myElement.Attribute("Value");
               VelocityMinStartY.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityEndMaxX");
               xVal = myElement.Attribute("Value");
               VelocityMaxStartY.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityEndMinY");
               xVal = myElement.Attribute("Value");
               VelocityMinEndY.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               myElement = subTree.Element("VelocityEndMaxY");
               xVal = myElement.Attribute("Value");
               VelocityMaxEndY.Value = Convert.ToDecimal(float.Parse(xVal.Value));

               //open Image
               OpenFileDialog imagedlg = new OpenFileDialog();
               imagedlg.Filter = "All Image Files ( JPEG,BMP,PNG )|*.jpg;*.jpeg;*.bmp;*.png;|JPEG Files ( *.jpg;*.jpeg )|*.jpg;*.jpeg|BMP Files ( *.bmp )|*.bmp|PNG Files ( *.png )|*.png| All Files (*.*)|*.*";

               if (DialogResult.OK == imagedlg.ShowDialog())
               {

                   System.IO.StreamReader reader = new System.IO.StreamReader(imagedlg.FileName);

                   if (particleImage != null)
                       TM.UnloadTexture(imageindex);

                   particleImage = imagedlg.FileName;
                   ImagePathTextBox.Text = imagedlg.SafeFileName;

                   reader.Close();
               }

               imageindex = TM.LoadTexture(particleImage);
           }
       }

       private void tabPage1_SizeChanged(object sender, EventArgs e)
       {
           if (this.Width < 460)
           {
               EmiterHScrollBar.Visible = true;
               EmiterHScrollBar.Enabled = true;
           }
           else if (this.Width >= 460)
           {
               EmiterHScrollBar.Visible = false;
               EmiterHScrollBar.Enabled = false;
           }

           if (this.Height < 880)
           {
               EmiterVScrollBar.Visible = true;
               EmiterVScrollBar.Enabled = true;
           }
           else if (this.Height >= 880)
           {
               EmiterVScrollBar.Visible = false;
               EmiterVScrollBar.Enabled = false;
           }
       }

       private void Form1_Resize(object sender, EventArgs e)
       {
           if (this.Height < 880)
           {
               EmiterVScrollBar.Visible = true;
               EmiterVScrollBar.Enabled = true;
           }
           else if (this.Height >= 880)
           {
               EmiterVScrollBar.Visible = false;
               EmiterVScrollBar.Enabled = false;
           }
       }

       //private int PointIsWithinLine(PointF one, PointF two, PointF check)
       //{
       //    int result = IsOnLine(one, two, check);
       //    if (result == 0) return 0;
       //    if (result == -1) return -1;
       //    float lo_x = (one.X < two.X) ? one.X : two.X;
       //    float hi_x = (one.X > two.X) ? one.X : two.X;
       //    float lo_y = (one.Y < two.Y) ? one.Y : two.Y;
       //    float hi_y = (one.Y > two.Y) ? one.Y : two.Y;
       //    if (check.X < lo_x) return 0;
       //    if (check.X > hi_x) return 0;
       //    if (check.X < lo_y) return 0;
       //    if (check.X > hi_y) return 0;
       //    return 1;
       //}

       //int IsOnLine(PointF startPoint, PointF endPoint, PointF checkPoint)
       //{
       //    if (startPoint.X == endPoint.X && startPoint.Y == endPoint.Y) //Not a line
       //        return -1;
       //    if (startPoint.X == endPoint.X)    //No gradient
       //        return (checkPoint.Y == startPoint.Y) ? 1 : 0;
       //    if (startPoint.Y == endPoint.Y)    //Infinite gradient
       //        return (checkPoint.X == startPoint.X) ? 1 : 0;

       //    double gradient = (endPoint.Y - startPoint.Y) / (endPoint.X - startPoint.X);
       //    //Line axis intercept
       //    double y01 = startPoint.Y - (startPoint.X * gradient);
       //    double x01 = startPoint.X - (startPoint.Y / gradient);
       //    //Test point axis intercept
       //    double y02 = checkPoint.Y - (checkPoint.X * gradient);
       //    double x02 = checkPoint.X - (checkPoint.Y / gradient);
       //    //If intercepts are the same then point is on line
       //    int y0 = ((int)(y02 + 0.5)) - ((int)(y01 + 0.5));
       //    int x0 = ((int)(x02 + 0.5)) - ((int)(x01 + 0.5));
       //    return (y0 == x0) ? 0 : 1;
       //}

       private bool IsOnLine(PointF startPoint, PointF endPoint, PointF checkPoint)
       {
           //double ab = Math.Sqrt(Math.Pow((startPoint.X - endPoint.X), 2.0f) + Math.Pow((startPoint.Y - endPoint.Y), 2.0f));
           //double ac = Math.Sqrt(Math.Pow((startPoint.X - checkPoint.X), 2.0f) + Math.Sqrt(Math.Pow((startPoint.Y - checkPoint.Y), 2.0f)));
           //double bc = Math.Sqrt(Math.Pow((endPoint.X - checkPoint.X), 2.0f) + Math.Sqrt(Math.Pow((endPoint.Y - checkPoint.Y), 2.0f)));

           //if (Math.Abs(ac + bc - ab) < 0.01f)
           //    return true;
           //else
           //    return false;

           float c1;
           float c2;

           if ((endPoint.Y - startPoint.Y) == 0.0f)
               c1 = 1;
           else
               c1 = (endPoint.Y - startPoint.Y);

           if ((endPoint.X - startPoint.X) == 0.0f)
               c2 = 1;
           else
               c2 = (endPoint.X - startPoint.X);

           return ((checkPoint.Y - startPoint.Y) / c1)
               == ((checkPoint.X - startPoint.X) / c2);
       }

     }
}



