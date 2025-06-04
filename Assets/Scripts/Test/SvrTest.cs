using Core.Net;

namespace Test
{
    internal class TestSvr : Svr
    {
        public TestSvr(out int c) : base(Port.PORT, out c) {}
    }
}