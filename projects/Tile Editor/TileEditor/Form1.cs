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
    public partial class Form1 : Form
    {
        // The current tile set.
        Bitmap bitmap = Properties.Resources._default;

        // Width and height of the current tile set in tiles.
        Size tileSetSize = new Size(4, 2);

        // Width and height of a single tile in pixels.
        Size tileSize = new Size(64, 64);

        // The current map.
        Tile[,] map = new Tile[5, 5];

        // Width and height of the current map in tiles.
        Size mapSize = new Size(5, 5);

        // The currently selected tile.
        Tile selectedTile;
        Point selectedPoint = new Point();
        Random random = new Random();



        public Form1()
        {

            InitializeComponent();
            TileGraphic.AutoScrollMinSize = bitmap.Size;
            //Adjust
            Graphics g = TileGraphic.CreateGraphics();
            bitmap.SetResolution(g.DpiX, g.DpiY);
            g.Dispose();
            graphicsPanel1.AutoScrollMinSize = new Size(mapSize.Width * tileSize.Width, mapSize.Height * tileSize.Height);
        }

        private void TileGraphic_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(bitmap, new Point(0, 0));

            Point bitmapsXY = new Point(0, 0);

            // Add AutoScrollPosition
            bitmapsXY.X += TileGraphic.AutoScrollPosition.X;
            bitmapsXY.Y += TileGraphic.AutoScrollPosition.Y;


            e.Graphics.DrawImage(bitmap, bitmapsXY);

            Rectangle SelectedRect = Rectangle.Empty;

            for (int x = 0; x < tileSetSize.Width; x++)
            {
                for (int y = 0; y < tileSetSize.Height; y++)
                {
                    // Calculate where the tile is going to be drawn in the map.
                    Rectangle rect = Rectangle.Empty;
                    rect.X = (x * tileSize.Width) + TileGraphic.AutoScrollPosition.X;
                    rect.Y = (y * tileSize.Height) + TileGraphic.AutoScrollPosition.Y;
                    rect.Size = tileSize;
                    Pen p = new Pen(Color.Black, 4.0f);
                    e.Graphics.DrawRectangle(p, rect);

                    //point pixel
                    if (rect.Contains(selectedPoint))
                    {
                        SelectedRect = rect;
                    }

                }
            }


            Pen sP = new Pen(Color.Red, 4.0f);
            e.Graphics.DrawRectangle(sP, SelectedRect);
            sP.Dispose();
        }

        private void TileGraphic_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Rectangle check = new Rectangle(0, 0, tileSetSize.Width * tileSize.Width, tileSetSize.Height * tileSize.Height);
            Point mouseXY = e.Location;

            mouseXY.X -= TileGraphic.AutoScrollPosition.X;
            mouseXY.Y -= TileGraphic.AutoScrollPosition.Y;

            if (check.Contains(e.Location))
            {
                selectedTile.X = mouseXY.X / tileSize.Width;
                selectedTile.Y = mouseXY.Y / tileSize.Height;
                selectedPoint = mouseXY;
            }
            TileGraphic.Invalidate();
        }



        private void graphicsPanel1_Paint(object sender, PaintEventArgs e)
        {


            for (int x = 0; x < mapSize.Width; x++)
            {
                for (int y = 0; y < mapSize.Height; y++)
                {
                    Rectangle destRect = Rectangle.Empty;
                    destRect.X = (x * tileSize.Width) + graphicsPanel1.AutoScrollPosition.X;
                    destRect.Y = (y * tileSize.Height) + graphicsPanel1.AutoScrollPosition.Y;
                    destRect.Size = tileSize;

                    Rectangle srcRect = Rectangle.Empty;
                    if (map[x, y].X == -1)
                    {
                        e.Graphics.FillRectangle(Brushes.White, destRect);
                        e.Graphics.DrawRectangle(Pens.Black, destRect);
                    }
                    else
                    {
                        srcRect.X = map[x, y].X * tileSize.Width;
                        srcRect.Y = map[x, y].Y * tileSize.Height;
                        srcRect.Size = tileSize;
                        e.Graphics.DrawImage(bitmap, destRect, srcRect, GraphicsUnit.Pixel);
                    }
                    e.Graphics.DrawRectangle(Pens.Black, destRect);
                }
            }

        }

        private void graphicsPanel1_MouseClick(object sender, MouseEventArgs e)
        {
            // Calculate the tile in which the mouse click occured.
            Rectangle check = new Rectangle(0, 0, mapSize.Width * tileSize.Width, mapSize.Height * tileSize.Height);
            if (check.Contains(e.Location))
            {
                int x = (e.X - graphicsPanel1.AutoScrollPosition.X) / tileSize.Width;
                int y = (e.Y - graphicsPanel1.AutoScrollPosition.Y) / tileSize.Height;

                // Set the selected tile in the map.
                map[x, y] = selectedTile;
                graphicsPanel1.Invalidate();

            }
        }

        private void graphicsPanel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (e.X < mapSize.Width * tileSize.Width && e.Y < mapSize.Height * tileSize.Height && e.X > 0 && e.Y > 0)
                {
                    int x = (e.X - graphicsPanel1.AutoScrollPosition.X) / tileSize.Width;
                    int y = (e.Y - graphicsPanel1.AutoScrollPosition.Y) / tileSize.Height;

                    // Set the selected tile in the map.
                    map[x, y] = selectedTile;
                    graphicsPanel1.Invalidate();
                }

            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            map = new Tile[5, 5];
            mapSize = new Size(5, 5);
            for (int i = 0; i < mapSize.Width; i++)
            {
                for (int j = 0; j < mapSize.Height; j++)
                {
                    map[i, j] = new Tile(-1, 0);
                }
            }
            selectedTile = new Tile(0, 0);
            selectedPoint = new Point(1, 1);

            bitmap = Properties.Resources._default;
            TileGraphic.AutoScrollMinSize = bitmap.Size;
            //Adjust
            Graphics g = TileGraphic.CreateGraphics();
            bitmap.SetResolution(g.DpiX, g.DpiY);
            g.Dispose();
            graphicsPanel1.AutoScrollMinSize = new Size(mapSize.Width * tileSize.Width, mapSize.Height * tileSize.Height);

            graphicsPanel1.Invalidate();
            TileGraphic.Invalidate();
        }


        private void modalDialogToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ModalDialog dlg = new ModalDialog();

            dlg.tileSetSizeHeight = tileSetSize.Height;
            dlg.tileSetSizeWidth = tileSetSize.Width;
            dlg.mapSizeHeight = mapSize.Height;
            dlg.mapSizeWidth = mapSize.Width;
            dlg.tileSize = tileSize.Width;
            dlg.myBitmap = bitmap;

            dlg.Apply += new ApplyEventHandler(dlg_Apply);
            if (DialogResult.OK == dlg.ShowDialog())
            {
                if (dlg.myBitmap != null)
                {
                    bitmap = new Bitmap(dlg.myBitmap);
                }
                tileSize.Width = dlg.tileSize;
                tileSize.Height = dlg.tileSize;

                tileSetSize.Width = dlg.tileSetSizeWidth;
                tileSetSize.Height = dlg.tileSetSizeHeight;


                Tile[,] aux = new Tile[dlg.mapSizeWidth, dlg.mapSizeHeight];
                Size auxSize = new Size(dlg.mapSizeWidth, dlg.mapSizeHeight);
                for (int i = 0; i < auxSize.Width; i++)
                {
                    for (int j = 0; j < auxSize.Height; j++)
                    {
                        if (i < mapSize.Width && j < mapSize.Height)
                        {
                            aux[i, j] = map[i, j];
                        }
                        else
                        {
                            aux[i, j] = new Tile(0, 0);
                        }
                    }
                }
                map = new Tile[dlg.mapSizeWidth, dlg.mapSizeHeight];
                mapSize = new Size(dlg.mapSizeWidth, dlg.mapSizeHeight);
                map = aux;

                Graphics g = TileGraphic.CreateGraphics();
                bitmap.SetResolution(g.DpiX, g.DpiY);
                g.Dispose();
                graphicsPanel1.AutoScrollMinSize = new Size(mapSize.Width * tileSize.Width, mapSize.Height * tileSize.Height);
                graphicsPanel1.Invalidate();
                TileGraphic.Invalidate();
                selectedTile = new Tile(0, 0);
                selectedPoint = new Point(1, 1);
            }
        }

        void dlg_Apply(object sender, ApplyEventArgs e)
        {
            if (e.Map != null)
            {
                bitmap = new Bitmap(e.Map);
            }
            tileSetSize.Width = e.TileSetSizeWidth;
            tileSetSize.Height = e.TileSetSizeHeight;

            tileSize.Width = e.TileSize;
            tileSize.Height = e.TileSize;

            Tile[,] aux = new Tile[e.MapSizeWidth, e.MapSizeHeight];
            Size auxSize = new Size(e.MapSizeWidth, e.MapSizeHeight);
            for (int i = 0; i < auxSize.Width; i++)
            {
                for (int j = 0; j < auxSize.Height; j++)
                {
                    if (i < mapSize.Width && j < mapSize.Height)
                    {
                        aux[i, j] = map[i, j];
                    }
                    else
                    {
                        aux[i, j] = new Tile(0, 0);
                    }
                }
            }
            map = new Tile[e.MapSizeWidth, e.MapSizeHeight];
            mapSize = new Size(e.MapSizeWidth, e.MapSizeHeight);
            map = aux;
            TileGraphic.AutoScrollMinSize = bitmap.Size;

            Graphics g = TileGraphic.CreateGraphics();
            bitmap.SetResolution(g.DpiX, g.DpiY);
            g.Dispose();
            graphicsPanel1.AutoScrollMinSize = new Size(mapSize.Width * tileSize.Width, mapSize.Height * tileSize.Height);
            graphicsPanel1.Invalidate();
            TileGraphic.Invalidate();
            selectedTile = new Tile(0, 0);
            selectedPoint = new Point(1, 1);

        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var saveFile = new SaveFileDialog();
            saveFile.Filter = "Tile Files (*.csv)|*.csv";
            if (saveFile.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                using (var sw = new System.IO.StreamWriter(saveFile.FileName, false))
                {
                    string file = tileSize.Width + "," + tileSize.Height + "," + tileSetSize.Width + "," + tileSetSize.Height + "," + mapSize.Width + "," + mapSize.Height;
                    sw.Write(file + Environment.NewLine);
                    // System.Text.StringBuilder sb = new System.Text.StringBuilder();
                    for (int j = 0; j < mapSize.Height; j++)
                    {
                        file = string.Empty;
                        for (int i = 0; i < mapSize.Width; i++)
                        {
                            if (i == 0)
                            {
                                file = ((map[i, j].Y * tileSetSize.Width) + map[i, j].X).ToString();
                            }
                            else
                            {
                                file = file + "," + ((map[i, j].Y * tileSetSize.Width) + map[i, j].X);
                            }

                        }
                        sw.Write(file + Environment.NewLine);
                    }
                }

            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files(*.*)|*.*|My Files(*.myf)|*.myf";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                int counter = 0;
                int j = 0;
                System.IO.StreamReader reader = new System.IO.StreamReader(dlg.FileName);
                using (var sr = new System.IO.StreamReader(dlg.FileName, false))
                    //the first line will always be there
                    while (sr.ReadLine() != null)
                    {
                        string line = reader.ReadLine();
                        char[] coma = { ',' };

                        string[] data = line.Split(coma);

                        if (counter == 0)
                        {
                            counter++;
                            tileSize = new Size(Convert.ToInt32(data[0]), Convert.ToInt32(data[1]));
                            tileSetSize = new Size(Convert.ToInt32(data[2]), Convert.ToInt32(data[3]));
                            map = new Tile[Convert.ToInt32(data[4]), Convert.ToInt32(data[5])];
                            mapSize = new Size(Convert.ToInt32(data[4]), Convert.ToInt32(data[5]));
                        }
                        else
                        {
                            for (int i = 0; i < mapSize.Width; i++)
                            {
                                if ((Convert.ToInt32(data[i]) % tileSetSize.Width) > (tileSetSize.Width * tileSetSize.Height) || (Convert.ToInt32(data[i]) / tileSetSize.Width) > (tileSetSize.Width * tileSetSize.Height))
                                {
                                    //if the index is greater than the actual tileSet maxIndex I will set it to the first tile.
                                    map[i, j] = new Tile(0, 0);
                                }
                                else
                                {
                                    map[i, j] = new Tile((Convert.ToInt32(data[i]) % tileSetSize.Width), (Convert.ToInt32(data[i]) / tileSetSize.Width));
                                }
                            }

                            j++;
                        }
                    }
                reader.Close();
            }

            graphicsPanel1.Invalidate();
            selectedTile = new Tile(0, 0);
            selectedPoint = new Point(1, 1);
        }

        private void toolWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < mapSize.Height; i++)
            {
                for (int j = 0; j < mapSize.Width; j++)
                {
                    map[i, j] = new Tile(random.Next(0, tileSetSize.Width), random.Next(0, tileSetSize.Height));
                }
            }
            graphicsPanel1.Invalidate();
        }


    }
}


