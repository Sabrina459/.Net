using System;
using System.Web;
using System.Collections.Generic;
using System.Web.Mvc;
using AutoMapper;
using BusinessLogic;
using DataBase.Entities;
using NUnit.Framework;
using DataBase.Interfaces;
using WebApplication.Controllers;
using Moq;

namespace WebApplication.Test
{
    public class HomeControllerTest
    {
        [Test]
        public void Index()
        {
            // Arrange
            var mock = new Mock<IOrderService>();
            
            mock.Setup(a => a.GetGoods()).Returns(new List<GoodDTO>());
            HomeController controller = new HomeController(mock.Object);
 
            // Act
            ViewResult result = controller.Index() as ViewResult;
 
            // Assert
            Assert.IsNotNull(result);
        }
 
        [Test]
        public void MakeOrder()
        {
            var id = 3;
            Type expected = new OrderView().GetType();
            var mock = new Mock<IOrderService>();
            mock.Setup(a => a.GetGood(id)).Returns(new GoodDTO{Id = id});
            HomeController controller = new HomeController(mock.Object);
            // Act
            ViewResult result = controller.MakeOrder(id) as ViewResult;
            // Assert
            Assert.IsNotNull(result);
            Assert.AreEqual(expected,result.Model.GetType());
        }
    }
}