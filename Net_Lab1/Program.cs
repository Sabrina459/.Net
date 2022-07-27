using System;
using System.Collections.Generic;
namespace Net_Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            MyCollection<int> list = new MyCollection<int>() {2,4,8,6 };
            List<int> list2 = new List<int>() { 2, 4, 8, 6 };
            Console.WriteLine(list2[0] +" " +list2.Count);
            Console.WriteLine(list2.Equals(list));


            list.Event += myCollection_Event;
            Console.WriteLine(list.toString());
            list.Add(1);
            list.Add(1);
            list.Add(2);
            list.Add(3);
            list.Add(4);
            list.Add(5);
            Console.WriteLine(list.toString());
            list.RemoveAt(4);
            Console.WriteLine(list.toString());
            Console.WriteLine(list.FindIndex(3));
            list.Insert(1, 8);
            Console.WriteLine(list.toString());
            list.Clear();
            Console.WriteLine(list.toString());

            
        }
        static void myCollection_Event(object sender, CollectionEventArgs e)
        {
            switch (e.Message)
            {
                case "Add":
                    Console.WriteLine($"Element was added");
                    break;
                case "Remove":
                    Console.WriteLine(String.Format("Element was removed"));
                    break;
                case "RemoveAt":
                    Console.WriteLine(String.Format($"Element was removed at {e.Index} index"));
                    break;
                case "Insert":
                    Console.WriteLine(String.Format($"Element was inserted at {e.Index}  index"));
                    break;
                case "Clear":
                    Console.WriteLine(String.Format("Collection was cleared"));
                    break;
                default:
                    Console.WriteLine("Something has happend");
                    break;
            }
        }

    }

}
