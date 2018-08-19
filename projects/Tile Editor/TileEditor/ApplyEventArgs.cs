using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;


namespace TileEditorSkeleton
{
    public class ApplyEventArgs : EventArgs
    {
        int mapSizeWidth;
        int mapSizeHeight;
        int tileSetSizeWidth;
        int tileSetSizeHeight;
        Bitmap map;
        int tileSize;



        public int MapSizeWidth
        {
            get
            {
                return mapSizeWidth;
            }
            set
            {
                mapSizeWidth = value;
            }
        }
        public int MapSizeHeight
        {
            get
            {
                return mapSizeHeight;
            }
            set
            {
                mapSizeHeight = value;
            }
        }

        public int TileSetSizeWidth
        {
            get
            {
                return tileSetSizeWidth;
            }
            set
            {
                tileSetSizeWidth = value;
            }
        }
        public int TileSetSizeHeight
        {
            get
            {
                return tileSetSizeHeight;
            }
            set
            {
                tileSetSizeHeight= value;
            }
        }
        public Bitmap Map
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
        public int TileSize
        {
            get
            {
                return tileSize;
            }
            set
            {
                tileSize = value;
            }
        }

        public ApplyEventArgs(int myMapSizeWidth, int myMapSizeHeight, int myTileSetSizeWidth, int myTileSetSizeHeight, Bitmap myMap,int myTileSize)
        {
            this.mapSizeWidth = myMapSizeWidth;
            this.mapSizeHeight = myMapSizeHeight;
            this.tileSetSizeWidth = myTileSetSizeWidth;
            this.tileSetSizeHeight = myTileSetSizeHeight;
            this.map = myMap;
            this.tileSize = myTileSize; 
        }
    }
}