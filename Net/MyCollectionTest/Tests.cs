using NUnit.Framework;
using MyCollection;


namespace MyCollectionTest
{
    [TestFixture]
    public class Tests
    {
        [Test]
        public void IntCollectionCreate_Test()
        {
            var expected = new int[0];
            var actual = new MyCollection<int>();
            Assert.AreEqual(expected,actual, message: "");
        }
    }
}