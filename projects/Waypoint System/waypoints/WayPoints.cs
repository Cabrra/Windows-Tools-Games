using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace midterm
{
    class WayPoints
    {
        string label;
        public string Label
        {
            get
            {
                return label;
            }
            set
            {
                label = value;
            }
        }

        bool isSelected;
        public bool IsSelected
        {
            get
            {
                return isSelected;
            }
            set
            {
                isSelected = value;
            }
        }

        int valueX;
        public int ValueX
        {
            get
            {
                return valueX;
            }
            set
            {
                valueX = value;
            }
        }

        int valueY;
        public int ValueY
        {
            get
            {
                return valueY;
            }
            set
            {
                valueY = value;
            }
        }

        Rectangle re;
        public Rectangle Rec
        {
            get
            {
                return re;
            }
            set
            {
                re = value;
            }
        }

        public override string ToString()
        {

            return label + " " + "(X = " + valueX + "   Y = " + valueY + ")";
        }

    }
}
