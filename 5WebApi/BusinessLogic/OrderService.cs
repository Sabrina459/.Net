using System;
using System.Collections.Generic;
using System.Linq;
using AutoMapper;
using DataBase.EF;
using DataBase.Entities;
using DataBase.Interfaces;
using DataBase.Repository;

namespace BusinessLogic
{
    public class OrderService : IOrderService
    {
        private readonly IUnitOfWork _unitOfWork;
 
        public OrderService(GoodContext gc)
        {
            _unitOfWork = new EFUnitOfWork(gc);
        }
        public void MakeOrder(OrderDTO orderDto)
        {
            
            bool _present = true;
            Good good = _unitOfWork.Goods.Get(orderDto.GoodId);
            
            // валидация
            if (good == null)
                throw new ValidationException("Товар не найден","");
            Order order = new Order
            {
                Id = orderDto.Id,
                
                Date = DateTime.Now,
                Address = orderDto.Address,
                GoodId = good.Id,
                Sum = good.Price,
                GoodQuantity = orderDto.GoodQuantity
            };
            _unitOfWork.Orders.Create(order);
            _unitOfWork.Save();
            
            if (good.Quantity < order.GoodQuantity)
            {
                Post post = new Post(_unitOfWork,order, order.GoodQuantity - good.Quantity+10);
                throw new ValidationException("Вашего товара сейчас нет на складе,\n заказ будет отгружен после доставки товара на склад", "");
            }
            else
            {
                good.Quantity -= order.GoodQuantity;
                _unitOfWork.Goods.Update(good);
            }

            _unitOfWork.Save();
            
        }

        public OrderDTO GetOrder(int id)
        {
            var mapper = new MapperConfiguration(cfg => cfg.CreateMap<Order, OrderDTO>()).CreateMapper();
            var order=  mapper.Map<Order, OrderDTO>(_unitOfWork.Orders.Get(id));
            if (order != null)
            {
                return order;
            }
            throw new ValidationException("Заказ не найден", "");
        }
        public int GetNewOrderId()
        {
            var order = _unitOfWork.Orders.GetLast();
            if (order == null)
            {
                return 1;
            }
            return order.Id+1;
        }

        public IEnumerable<GoodDTO> GetGoods()
        {
            var mapper = new MapperConfiguration(cfg => cfg.CreateMap<Good, GoodDTO>()).CreateMapper();
            return mapper.Map<IEnumerable<Good>, List<GoodDTO>>(_unitOfWork.Goods.GetAll());
            
        }
 
        public GoodDTO GetGood(int? id)
        {
            if (id == null)
                throw new ValidationException("Не установлено id товара","");
            var good = _unitOfWork.Goods.Get(id.Value);
            if (good == null)
                throw new ValidationException("Товар не найден","");
             
            return new GoodDTO { Id = good.Id, Name = good.Name, Price = good.Price};
        }
 
        public void Dispose()
        {
            _unitOfWork.Dispose();
        }
    }
}