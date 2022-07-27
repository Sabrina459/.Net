namespace PresentationLayer
{
    public class OrderView
    {
        public int Id { get; set; }
        public int GoodId { get; set; }
        public string Status { get; }
        public decimal Sum { get; }

        public string Address { get; set; }
        public int GoodQuantity { get; set; }
    }
}