using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tool
{
    class ParticleFlyweight
    {
        float minLife;
        public float MinLife
        {
            get
            {
                return minLife;
            }
            set
            {
                minLife = value;
            }
        }

        float maxLife;
        public float MaxLife
        {
            get
            {
                return maxLife;
            }
            set
            {
                maxLife = value;
            }
        }

        float rotationS;
        public float RotationStart
        {
            get
            {
                return rotationS;
            }
            set
            {
                rotationS = value;
            }
        }

        float rotationE;
        public float RotationEnd

        {
            get
            {
                return rotationE;
            }
            set
            {
                rotationE = value;
            }
        }

        float scaleS;
        public float ScaleStart
        {
            get
            {
                return scaleS;
            }
            set
            {
                scaleS = value;
            }
        }

        float scaleE;
        public float ScaleEnd
        {
            get
            {
                return scaleE;
            }
            set
            {
                scaleE = value;
            }
        }

        //color
        float alphaS;
        public float AlphaStart
        {
            get
            {
                return alphaS;
            }
            set
            {
                alphaS = value;
            }
        }

        float redS;
        public float RedStart
        {
            get
            {
                return redS;
            }
            set
            {
                redS = value;
            }
        }

        float greenS;
        public float GreenStart
        {
            get
            {
                return greenS;
            }
            set
            {
                greenS = value;
            }
        }

        float blueS;
        public float BlueStart
        {
            get
            {
                return blueS;
            }
            set
            {
                blueS = value;
            }
        }

        float alphaE;
        public float AlphaEnd
        {
            get
            {
                return alphaE;
            }
            set
            {
                alphaE = value;
            }
        }

        float redE;
        public float RedEnd
        {
            get
            {
                return redE;
            }
            set
            {
                redE = value;
            }
        }

        float greenE;
        public float GreenEnd
        {
            get
            {
                return greenE;
            }
            set
            {
                greenE = value;
            }
        }

        float blueE;
        public float BlueEnd
        {
            get
            {
                return blueE;
            }
            set
            {
                blueE = value;
            }
        }
        
        //velocity
        float velSMinX;
        public float VelStartMinX
        {
            get
            {
                return velSMinX;
            }
            set
            {
                velSMinX = value;
            }
        }
        
        float velSMaxX;
        public float VelStartMaxX
        {
            get
            {
                return velSMaxX;
            }
            set
            {
                velSMaxX = value;
            }
        }

        float velSMinY;
        public float VelStartMinY
        {
            get
            {
                return velSMinY;
            }
            set
            {
                velSMinY = value;
            }
        }

        float velSMaxY;
        public float VelStartMaxY
        {
            get
            {
                return velSMaxY;
            }
            set
            {
                velSMaxY = value;
            }
        }

        float velEMinX;
        public float VelEndMinX
        {
            get
            {
                return velEMinX;
            }
            set
            {
                velEMinX = value;
            }
        }

        float velEMaxX;
        public float VelEndMaxX
        {
            get
            {
                return velEMaxX;
            }
            set
            {
                velEMaxX = value;
            }
        }

        float velEMinY;
        public float VelEndMinY
        {
            get
            {
                return velEMinY;
            }
            set
            {
                velEMinY = value;
            }
        }

        float velEMaxY;
        public float VelEndMaxY
        {
            get
            {
                return velEMaxY;
            }
            set
            {
                velEMaxY = value;
            }
        }
        
    }
}
