using System;
using DataBase.EF;
using DataBase.Entities;
using DataBase.Interfaces;

namespace DataBase.Repository
{
    public class EFUnitOfWork : IUnitOfWork
    {
        private GoodContext db;
        private GoodRepository goodRepository;
        private OrderRepository orderRepository;

        public EFUnitOfWork(GoodContext gc)
        {
            db = gc;
        }
        public IRepository<Good> Goods
        {
            get
            {
                if (goodRepository == null)
                    goodRepository = new GoodRepository(db);
                return goodRepository;
            }
        }

        public IRepository<Order> Orders
        {
            get
            {
                if (orderRepository == null)
                    orderRepository = new OrderRepository(db);
                return orderRepository;
            }
        }

        public void Save()
        {
            db.SaveChanges();
        }

        private bool disposed;

        public virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    db.Dispose();
                }

                disposed = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
    }
}