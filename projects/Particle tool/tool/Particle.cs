using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tool
{
    class Particle
    {
        float originalLife;
        public float Original
        {
            get
            {
                return originalLife;
            }
            set
            {
                originalLife = value;
            }
        }

        float currLife;
        public float CurrentLife
        {
            get
            {
                return currLife;
            }
            set
            {
                currLife = value;
            }
        }

        float currPositionX;
        public float CurrentPositionX
        {
            get
            {
                return currPositionX;
            }
            set
            {
                currPositionX = value;
            }
        }

        float currPositionY;
        public float CurrentPositionY
        {
            get
            {
                return currPositionY;
            }
            set
            {
                currPositionY = value;
            }
        }

        float colorCurrA;
        public float CurrentAlpha
        {
            get
            {
                return colorCurrA;
            }
            set
            {
                colorCurrA = value;
            }
        }

        float colorCurrR;
        public float CurrentRed
        {
            get
            {
                return colorCurrR;
            }
            set
            {
                colorCurrR = value;
            }
        }

        float colorCurrG;
        public float CurrentGreen
        {
            get
            {
                return colorCurrG;
            }
            set
            {
                colorCurrG = value;
            }
        }

        float colorCurrB;
        public float CurrentBlue
        {
            get
            {
                return colorCurrB;
            }
            set
            {
                colorCurrB = value;
            }
        }

        float scaleCurr;
        public float CurrentScale
        {
            get
            {
                return scaleCurr;
            }
            set
            {
                scaleCurr = value;
            }
        }

        float rotationCurr;
        public float CurrentRotation
        {
            get
            {
                return rotationCurr;
            }
            set
            {
                rotationCurr = value;
            }
        }

        float velocityCurrX;
        public float CurrentVelocityX
        {
            get
            {
                return velocityCurrX;
            }
            set
            {
                velocityCurrX = value;
            }
        }

        float velocityCurrY;
        public float CurrentVelocityY
        {
            get
            {
                return velocityCurrY;
            }
            set
            {
                velocityCurrY = value;
            }
        }

        float changeVelX;
        public float ChangeVelocityX
        {
            get
            {
                return changeVelX;
            }
            set
            {
                changeVelX = value;
            }
        }

        float changeVelY;
        public float ChangeVelocityY
        {
            get
            {
                return changeVelY;
            }
            set
            {
                changeVelY = value;
            }
        }

    }
}
