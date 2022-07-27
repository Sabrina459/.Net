using System;

namespace BusinessLogic
{
    public class OrderDTO
    {
        public int Id { get; set; }
        public decimal Sum { get; set; }
        public string Address { get; set; }
        public int GoodQuantity { get; set; }
        public int GoodId { get; set; }
        public string Status { get; set; }
 
        public DateTime? Date { get; set; }
    }
}