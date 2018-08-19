using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tool
{
    public class ApplyEventArgs : EventArgs
    {
        bool positionCh;

        public bool PositionChec
        {
            get
            {
                return positionCh;
            }
            set
            {
                positionCh = value;
            }
        }

        bool particleInfoCh;

        public bool ParticleInfoChec
        {
            get
            {
                return particleInfoCh;
            }
            set
            {
                particleInfoCh = value;
            }
        }

        bool emitterTypeCh;

        public bool EmitterTypeChec
        {
            get
            {
                return emitterTypeCh;
            }
            set
            {
                emitterTypeCh = value;
            }
        }

        bool emitterInfoCh;

        public bool EmitterInfoChec
        {
            get
            {
                return emitterInfoCh;
            }
            set
            {
                emitterInfoCh = value;
            }
        }

        bool basicICh;

        public bool BasicInfoChec
        {
            get
            {
                return basicICh;
            }
            set
            {
                basicICh = value;
            }
        }

        bool colorCh;

        public bool ColorChec
        {
            get
            {
                return colorCh;
            }
            set
            {
                colorCh = value;
            }
        }

        bool velXCh;

        public bool VeloXChec
        {
            get
            {
                return velXCh;
            }
            set
            {
                velXCh = value;
            }
        }

        bool velYCh;

        public bool VeloYChec
        {
            get
            {
                return velYCh;
            }
            set
            {
                velYCh = value;
            }
        }

        public ApplyEventArgs(bool pos, bool partI, bool emitterTyp, bool emitterInf, bool basic, bool color, bool velX, bool velY)
        {
            this.positionCh = pos;
            this.particleInfoCh = partI;
            this.emitterTypeCh = emitterTyp;
            this.emitterInfoCh = emitterInf;
            this.basicICh = basic;
            this.colorCh = color;
            this.velXCh = velX;
            this.velYCh = velY;
        }

    }
}
