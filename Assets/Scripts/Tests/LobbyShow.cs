using UnityEngine;
using Core.Net;
using Core;
using Unity.VisualScripting;
using ParrelSync;
using System.Runtime.InteropServices;

namespace Tests
{
    internal class LobbyShow : MonoBehaviour
    {
        public void Awake()
        {
#if UNITY_EDITOR
            if (true)
            {
                Debug.Log("Hello World!");
                int a = 0;
                if (a == 0)
                {
                    Wrap.Net.Cli cli = new Wrap.Net.Cli("127.0.0.1", Port.PORT);
                    Wrap.RoomArr rooms = cli.ReqRoomShow(0, 5);

                    foreach (Wrap.Room r in rooms)
                    {
                        Debug.Log($"Name: {r.name}");
                        Debug.Log($"Started: {r.r.m_started}");
                        Debug.Log($"Member count: {r.r.m_member}");
                    }
                }
            }
#else
            else
            {
                int d;
                Svr a = new TestSvr(out d);
                Debug.Log($"This is svr end: {d}");
            }
#endif
        }
    }
}
