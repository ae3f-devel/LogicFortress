using System;
using System.Runtime.InteropServices;

namespace Core.Net
{
    /// <summary>
    /// This works as singleton itself automatically.
    /// </summary>
    public class Sock
    {
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public static extern int SockOpen();

        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public static extern void SockClose(int a);

        private int _fd;
        public int fd { get { return _fd; } }


        public Sock()
        {
            this._fd = SockOpen();
        }

        ~Sock()
        {
            SockClose(this._fd);
        }
    }
}