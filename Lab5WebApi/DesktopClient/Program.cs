using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;
using DataBase.Entities;
using PresentationLayer;

namespace DesktopClient
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                GetRequest("GetGoods").Wait();
                Console.WriteLine("Enter \"Make\" to make order or \"Check\" to check order:");
                string id = Console.ReadLine();

                GetRequest(id).Wait();
                Console.ReadKey();
                Console.Clear();
            }
        }
        
        static async Task GetRequest(string ID)
        {
            switch (ID)
            {
                //Get Request    
                case "GetGoods":
                    using (var client = new HttpClient())
                    {
                        client.BaseAddress = new Uri("https://localhost:5001/");
                        client.DefaultRequestHeaders.Accept.Clear();
                        client.DefaultRequestHeaders.Accept.Add(
                           new MediaTypeWithQualityHeaderValue("application/json"));

                        HttpResponseMessage response;
                        response = await client.GetAsync("api/Home");
                        if (response.IsSuccessStatusCode)
                        {
                            List<GoodView> reports = await response.Content.ReadAsAsync<List<GoodView>>();
                            foreach (var report in reports)
                            {
                                Console.WriteLine("\n{0}\t{1}\t{2}\t{3}", report.Id, report.Name, report.Price,
                                    report.Quantity);
                            }
                        }
                    }

                    break;
                case "Make":
                    Console.WriteLine("Enter id:");
                    int id = Convert.ToInt32(Console.ReadLine());
                    using (var client = new HttpClient())
                    {
                        client.BaseAddress = new Uri("https://localhost:5001/");
                        client.DefaultRequestHeaders.Accept.Clear();
                        client.DefaultRequestHeaders.Accept.Add(
                            new MediaTypeWithQualityHeaderValue("text/plain"));

                        HttpResponseMessage response;
                        response = await client.GetAsync($"api/Home/3?id={id}");
                        if (response.IsSuccessStatusCode)
                        {
                            OrderView order = await response.Content.ReadAsAsync<OrderView>();
                            Console.WriteLine("\nOrder Id:  {0}\n Input address:", order.Id);
                            string address = Console.ReadLine();
                            Console.WriteLine("Input Quantity");
                            int quantity = 0;
                            Int32.TryParse(Console.ReadLine(), out quantity);
                            while (quantity <= 0)
                            {
                                Console.WriteLine("Please, enter the valid quantity");
                                Int32.TryParse(Console.ReadLine(), out quantity);
                            }

                            Console.WriteLine("Tap enter to make order");
                            Console.ReadLine();
                            HttpResponseMessage make = await client.PostAsJsonAsync("", new OrderView
                            {
                                Id = order.Id,
                                Address = address,
                                GoodQuantity = quantity,
                                GoodId = id
                            });

                            if (make.IsSuccessStatusCode)
                            {
                                Console.WriteLine(await make.Content.ReadAsAsync<string>());
                                Console.WriteLine("Tab any key to return to the home page");
                                Console.ReadLine();

                            }
                        }

                    }

                    break;
                case "Check":
                    Console.WriteLine("Enter order id:");
                    int orderId = Convert.ToInt32(Console.ReadLine());
                    using (var client = new HttpClient())
                    {
                        client.BaseAddress = new Uri("https://localhost:5001");
                        client.DefaultRequestHeaders.Accept.Clear();
                        client.DefaultRequestHeaders.Accept.Add(
                            new MediaTypeWithQualityHeaderValue("application/json"));

                        HttpResponseMessage response;
                        response = await client.GetAsync($"/api/Home/1/checkOrder?id={orderId}");
                        if (response.IsSuccessStatusCode)
                        {
                            OrderView order = await response.Content.ReadAsAsync<OrderView>();
                            Console.WriteLine("\nOrder Id:  {0}\nStatus:    {1}\nAddress:   {2}\nSum:   {3}", order.Id, order.Status,
                                order.Address, order.Sum);
                        }
                        Console.WriteLine("To return to the home page tab any key");
                        Console.ReadLine();
                        break;
                    }
            }
        }
    }
}