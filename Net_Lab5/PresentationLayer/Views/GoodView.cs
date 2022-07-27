using System.Collections;

namespace PresentationLayer
{
    public class GoodView : IEnumerable
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Quantity{ get; set; } 
        public int Price { get; set; }

        public IEnumerator GetEnumerator()
        {
            throw new System.NotImplementedException();
        }
    }
}