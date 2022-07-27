using System.Data.Entity;
using DataBase.Entities;
using Microsoft.EntityFrameworkCore;
using DbContext = Microsoft.EntityFrameworkCore.DbContext;


namespace DataBase.EF
{
    public class GoodContext: DbContext
    {
        public System.Data.Entity.DbSet<Good> Goods { get; set; }
        public System.Data.Entity.DbSet<Order> Orders { get; set; }
        public GoodContext(DbContextOptions<GoodContext> options) : base(options) 
        { }

    }
    
}