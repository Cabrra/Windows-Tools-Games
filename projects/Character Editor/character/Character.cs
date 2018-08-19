using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace intro
{
    public class Character
    {
        string firstN;

        public string FistName
        {
            get
            {
                return firstN;
            }
            set
            {
                firstN = value;
            }
        }

        string lastN;

        public string LastName
        {
            get
            {
                return lastN;
            }
            set
            {
                lastN = value;
            }
        }

        decimal age;

        public decimal Age
        {
            get { return age; }
            set { age = value; }
        }
        CharacterRace race;

        public CharacterRace Races
        {
            get { return race; }
            set { race = value; }
        }


        public CharacterSkills skills;

        public Character()
        {

        }

        public override string ToString()
        {

            return firstN + " " + lastN;
        }

    }
}
