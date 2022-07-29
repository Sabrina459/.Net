namespace PresentationLayer
{
    public class OrderCheckView
    {
        public int Id { get; set; }
        public int GoodId { get; set; }

        public string GoodName { get; set; }
        public string Status { get; }
        public string Address { get; set; }
        public int GoodQuantity { get; set; }
    }
}