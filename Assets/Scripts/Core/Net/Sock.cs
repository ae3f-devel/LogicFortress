using System;
using System.Runtime.InteropServices;

namespace Core.Net
{
    /// <summary>
    /// This works as singleton itself automatically.
    /// </summary>
    public class Sock
    {
        [DllImport("liblibCli", CharSet = CharSet.Ansi)]
        public static extern int SockOpen();

        [DllImport("liblibCli", CharSet = CharSet.Ansi)]
        public static extern void SockClose();

        private int _fd;
        public int fd { get { return _fd; } }


        public Sock()
        {

        }

        ~Sock()
        {

        }
    }
}