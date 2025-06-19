using UnityEngine;
using Core.Net;
using Core;
using Unity.VisualScripting;
using ParrelSync;
using System.Runtime.InteropServices;
using System.Linq;

namespace Tests
{
    internal class LobbyShow : MonoBehaviour
    {
        unsafe public void Awake()
        {
#if UNITY_EDITOR
            if (!ClonesManager.IsClone())
            {
                Logger.AssignDebugLog();

                Debug.Log("Hello World!");
                int a = 0;
                if (a == 0)
                {
                    Wrap.Net.Cli cli = new Wrap.Net.Cli("127.0.0.1", Port.PORT);
                    var rooms = cli.ReqRoomShow(0, 5);

                    Debug.Log("Wrap room index");
                    for (uint i = 0; i < rooms.Count(); i++)
                    {
                        Room r = rooms[i];
                        Debug.Log($"Name: {r.name}");
                        Debug.Log($"Started: {r.m_started}");
                        Debug.Log($"Member count: {r.m_member}");
                    }
                    
                    Debug.Log("Wrap foreach");
                    foreach (Room r in rooms)
                    {
                        Debug.Log($"Name: {r.name}");
                        Debug.Log($"Started: {r.m_started}");
                        Debug.Log($"Member count: {r.m_member}");
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
