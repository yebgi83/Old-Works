using System;
using System.Collections;
using System.Text;
using System.Windows.Forms; 

namespace SpritePacker
{
    public class SpriteItemSorter : IComparer
    {
        public Int32 Compare(Object objA, Object objB)
        {
            ListViewItem lviItemA = objA as ListViewItem;
            ListViewItem lviItemB = objB as ListViewItem;

            return String.Compare(lviItemA.Text, lviItemB.Text);
        }
    }
}
