using DataBase.Entities;
using Microsoft.EntityFrameworkCore;
using DbContext = Microsoft.EntityFrameworkCore.DbContext;


namespace DataBase.EF
{
    public class GoodContext: DbContext
    {
        public DbSet<Good> Goods { get; set; }
        public DbSet<Order> Orders { get; set; }
        public GoodContext(DbContextOptions<GoodContext> options) : base(options) 
        { }

    }
    
}