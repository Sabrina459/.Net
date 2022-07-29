using DataBase.Entities;
using System;
namespace DataBase.Interfaces
{
    public interface IUnitOfWork : IDisposable
    {
        IRepository<Good> Goods { get;}
        IRepository<Order> Orders { get;}
        void Save();
    }
}