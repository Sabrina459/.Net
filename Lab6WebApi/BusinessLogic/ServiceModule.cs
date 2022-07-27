using DataBase.EF;
using DataBase.Interfaces;
using DataBase.Repository;
using Ninject.Modules;

namespace BusinessLogic
{
    public class ServiceModule : NinjectModule
    {
        private GoodContext connectionString;

        public ServiceModule(GoodContext connection)
        {
            connectionString = connection;
        }

        public override void Load()
        {
            Bind<IUnitOfWork>().To<EFUnitOfWork>().WithConstructorArgument(connectionString);
        }
    }
}