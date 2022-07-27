using System;
using System.Collections.Generic;
namespace DataBase.Interfaces
{
    public interface IRepository<T> where T : class
    {
        IEnumerable<T> GetAll();
        T GetLast();
        T Get(int id);
        Boolean GetStatus(int id);
        void  Create(T item);
        void Update(T item);
        void Delete(int id);
    }
}