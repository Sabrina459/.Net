using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Net_Lab2._1
{
    class MyCollectionEventArgs: EventArgs
    {
        public MyCollectionEventArgs(string message, int index)
        {
            Message = message;
            Index = index;
        }

        public string Message { get; private set; }
        public int Index { get; private set; }
    }
}
