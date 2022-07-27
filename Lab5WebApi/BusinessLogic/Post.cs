using System;
using DataBase.Entities;
using DataBase.Interfaces;

namespace BusinessLogic
{
    public class Post
    {
        public int Quantity { get; set; }
        public Order Order { get;}
        private readonly IUnitOfWork _database;

        public Post(IUnitOfWork unitOfWork, Order o, int quantity)
        {
            Order = o;
            Quantity = quantity;
            _database = unitOfWork;

            Book();
        }

        public void Book()
        {
            Console.WriteLine("The good is on the way");
            Order.Status = "Ожидается прибытие заказа";
            _database.Orders.Update(Order);
            _database.Save();
        }
    }
}