using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Net_Lab1
{
    public class Node<T>
    {
        public void SetNextNode(Node<T> _nextNode)
        {
            this.next = _nextNode;
        }

        public T Element
        {
            get
            {
                return this.element;
            }
            set
            {
                this.element = value;
            }
        }

        public Node<T> Next
        {
            get
            {
                return this.next;
            }
        }

        private Node<T> next;
        private T element;
    }
}
