using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using Net_Lab2._1;

namespace MyCollection.Tests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void IntEmptyCollectionCreate_Test()
        {
            var expected = 0;
            var actual = new MyCollection<int>();
            Assert.AreEqual(expected ,actual.Count, message: "The collection is not empty");
        }
            
        [TestMethod]
        public void IntNonEmptyCollectionCreate_Test()
        {
            var expectedCount = 4;
            var actual = new MyCollection<int>() {2, 4, 8, 6};
            Assert.IsTrue(expectedCount + " " +2  == actual.Count + " " + actual[0], message: "The collection items are not as expected");
        }
        [TestMethod]

        public void IntAddElement3_Test()
        {
            var toadd = 3;
            var actual = new MyCollection<int>();
            actual.Add(toadd);
            Assert.IsTrue(actual.Contains(toadd), message: "The collection does not consist the added element");
        }


        [TestMethod]
        public void IntInsertElement3at2_Test()
        {
            var expected = 3;
            var actual = new MyCollection<int>() { 2, 4, 8, 6 };
            actual.Insert(2,3);
            Assert.AreEqual(actual[2],expected, message: "The collection does not consist the inserted element at expected index");
        }
        [TestMethod]

        public void IntRemoveElement3_Test()
        {
            var toadd = 3;
            var actual = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            actual.Remove(toadd);
            Assert.IsFalse(actual.Contains(toadd), message: "The collection consists the removed element");
        }
        [TestMethod]

        public void IntRemoveElementNotExist_Test()
        {
            var toadd = 3;
            var actual = new MyCollection<int>() { 2, 4, 8, 6 };
            
            Assert.IsFalse(actual.Remove(toadd), message: "The element shouldn't be removed");
        }

        [TestMethod]
        public void IntRemoveElementat2_Test()
        {
            var expected = new List<int>() { 2, 4, 8, 6 };
            var actual = new MyCollection<int>() { 2, 4, 3, 8, 6 } ;
            actual.RemoveAt(2);
            Assert.AreEqual(actual[2], expected[2], message: "The element at index 2 was not removed");
        }

    
        [TestMethod]
        public void IntFindIndexof5notExist_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var expected = -1;
            var actual = array.FindIndex(5);
            Assert.AreEqual(expected,actual, message: "The actual index is not as expected");
        }
        [TestMethod]
        public void IntFindIndexof3Exist_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var expected = 2;
            var actual = array.FindIndex(3);
            Assert.AreEqual(expected, actual, message: "The actual index is not as expected");
        }

        [TestMethod]
        public void IntCollectionClear_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var expected = new MyCollection<int>();
            array.Clear();
            Assert.AreEqual(expected.Count, array.Count, message: "The collection was not cleared");
        }
        [TestMethod]
        public void IntCollectiontoString_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var expected = '3';
            Assert.AreEqual(expected, array.toString()[7], message: "The collection was not cleared");
        }
        [TestMethod]
        public void IndexIsOutofRangelower_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var ex = Assert.ThrowsException<IndexOutOfRangeException>(() => array[-5]);
            Assert.AreEqual(ex.Message, "Index was outside the bounds of the array.", message: "The exception was expected");
        }
        [TestMethod]
        public void IndexIsOutofRangebigger_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var ex = Assert.ThrowsException<IndexOutOfRangeException>(() => array[5]);
            Assert.AreEqual(ex.Message, "Index was outside the bounds of the array.", message: "The exception was expected");
        }

        [TestMethod]
        public void foreach_Test()
        {
            var array = new MyCollection<int>() { 2, 4, 3, 8, 6 };
            var expected = new List<int>();
            foreach (var item in array)
            {
                expected.Add(item);
            }
            Assert.AreEqual(expected.Count, array.Count, message: "Foreach works incorectly");
        }
    }
}
