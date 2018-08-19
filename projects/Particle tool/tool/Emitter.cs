using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tool
{
    class Emitter
    {
        string imageP;
        public string ImagePath
        {
            get
            {
                return imageP;
            }
            set
            {
                imageP = value;
            }
        }

        float width;
        public float EmitterWidth
        {
            get
            {
                return width;
            }
            set
            {
                width = value;
            }
        }

        float height;
        public float EmitterHeight
        {
            get
            {
                return height;
            }
            set
            {
                height = value;
            }
        }

        float positionX;
        public float EmitterPositionX
        {
            get
            {
                return positionX;
            }
            set
            {
                positionX = value;
            }
        }

        float positionY;
        public float EmitterPositionY
        {
            get
            {
                return positionY;
            }
            set
            {
                positionY = value;
            }
        }

        float spreadX;
        public float SpreadX
        {
            get
            {
                return spreadX;
            }
            set
            {
                spreadX = value;
            }
        }

        float spreadY;
        public float SpreadY
        {
            get
            {
                return spreadY;
            }
            set
            {
                spreadY = value;
            }
        }

        float spawn;
        public float SpawnRate
        {
            get
            {
                return spawn;
            }
            set
            {
                spawn = value;
            }
        }

        float firstW;
        public float FirstWave
        {
            get
            {
                return firstW;
            }
            set
            {
                firstW = value;
            }
        }

        float maxParticles;
        public float MaxParticles
        {
            get
            {
                return maxParticles;
            }
            set
            {
                maxParticles = value;
            }
        }
    }
}
