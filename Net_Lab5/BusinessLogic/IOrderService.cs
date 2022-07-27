using System.Collections.Generic;
using DataBase.Entities;
using DataBase.Repository;

namespace BusinessLogic
{
    public interface IOrderService
    {
        void MakeOrder(OrderDTO orderDto);
        int GetNewOrderId();
        OrderDTO GetOrder(int id);
        GoodDTO GetGood(int? id);
        IEnumerable<GoodDTO> GetGoods();
        void Dispose();
    }
}