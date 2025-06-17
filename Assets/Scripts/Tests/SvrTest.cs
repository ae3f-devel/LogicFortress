using Core.Net;

namespace Tests
{
    internal class TestSvr : Svr
    {
        public TestSvr(out int c) : base(Port.PORT, out c) {}
    }
}