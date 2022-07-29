using BusinessLogic;
using Ninject.Modules;

namespace PresentationLayer
{
    public class OrderModule: NinjectModule
    {
        public override void Load()
        {
            Bind<IOrderService>().To<OrderService>();
        }
    }
}