using System.Collections.Generic;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using DataBase.EF;
using DataBase.Entities;
using DataBase.Interfaces;

namespace DataBase.Repository
{
    public class GoodRepository: IRepository<Good>
    {
        private GoodContext db;
 
        public GoodRepository(GoodContext context)
        {
            this.db = context;
        }
 
        public IEnumerable<Good> GetAll()
        {
            return db.Goods;
        }

        public Good GetLast()
        {
            return db.Goods.LastOrDefault();
        }

        public Good Get(int id)
        {
            return db.Goods.Find(id);
        }

        public bool GetStatus(int id)
        {
            var g = db.Goods.Find(id);
            if (g !=null)
            {
                return g.Quantity != 0;
            }

            return false;

        }

        public void Create(Good item)
        {
            db.Goods.Add(item);
        }
 
        public void Update(Good item)
        {
            db.Entry(item).State = EntityState.Modified;
        }

        public void Delete(int id)
        {
            Good book = db.Goods.Find(id);
            if (book != null)
                db.Goods.Remove(book);
        }
    }
}