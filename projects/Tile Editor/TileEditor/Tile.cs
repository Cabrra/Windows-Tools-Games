using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileEditorSkeleton
{
    /// <summary>
    /// Structure representing a single tile.
    /// </summary>
    public struct Tile
    {
        int x;

        /// <summary>
        /// Gets or sets the X.
        /// </summary>
        public int X
        {
            get { return x; }
            set { x = value; }
        }

        int y;

        /// <summary>
        /// Gets or sets the Y.
        /// </summary>
        public int Y
        {
            get { return y; }
            set { y = value; }
        }

        /// <summary>
        /// Initializes a new instance of the Tile structure.
        /// </summary>
        public Tile(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
