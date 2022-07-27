using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using DataBase.Entities;
using DataBase.EF;
using DataBase.Interfaces;

namespace DataBase.Repository
{
    public class OrderRepository : IRepository<Order>
    {
        private GoodContext db;
 
        public OrderRepository(GoodContext context)
        {
            db = context;
        }
 
        public IEnumerable<Order> GetAll()
        {
            return db.Orders.Include(o => o.Good);
        }
 
        public Order Get(int id)
        {
            return db.Orders.Find(id);
        }

        public Boolean GetStatus(int id)
        {
            var g = db.Goods.Find(id);
            if (g != null)
            {
                return g.Quantity != 0;
            }

            return false;
        }
        public void Create(Order order)
        {
            db.Orders.Add(order);
            
        }
 
        public void Update(Order order)
        {
            db.Entry(order).State = EntityState.Modified;
        }
        public IEnumerable<Order> Find(Func<Order, Boolean> predicate)
        {
            return db.Orders.Include(o => o.Good).Where(predicate).ToList();
        }
        public void Delete(int id)
        {
            Order order = db.Orders.Find(id);
            if (order != null)
                db.Orders.Remove(order);
        }
    }
}