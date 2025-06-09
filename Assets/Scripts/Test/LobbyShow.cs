using UnityEngine;
using Core.Net;
using Core;
using Unity.VisualScripting;

namespace Test
{
    internal class LobbyShow : MonoBehaviour
    {
        public void Awake()
        {
            int a = 0;
            if (a == 0)
            {
                Room[] rooms = new Room[5];

                unsafe
                {
                    fixed (Room* _r = rooms)
                    {
                        Sock sock = new Sock();
                        SockAddr addr = new SockAddr("127.0.0.1", Port.PORT);
                        uint retcount;

                        Cli.ReqRoomShow(sock.fd, in addr, 0, 5, _r, out retcount);

                        Debug.Log($"Count: {retcount}");
                    }
                }
            }
        }
    }
}
