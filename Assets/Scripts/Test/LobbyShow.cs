using UnityEngine;
using Core.Net;
using Core;
using Unity.VisualScripting;

namespace Test
{
    public class LobbyShow : MonoBehaviour
    {
        public void Awake()
        {
            int a;
            /** TODO: IMPLEMENT THIS */
            Svr svr = new Svr(8080, out a);
            if (a == 0)
            {
                _Room[] rooms = new _Room[5];
                
                unsafe
                {
                    fixed (_Room* _r = rooms)
                    {
                        Sock sock = new Sock();
                        SockAddr addr = new SockAddr("127.0.0.1", 8080);
                        uint retcount;

                        Cli.ReqRoomShow(sock.fd, in addr, 0, 5, _r, out retcount);

                        Debug.Log($"Count: {retcount}");
                    }
                }
            }
        }
    }
}
