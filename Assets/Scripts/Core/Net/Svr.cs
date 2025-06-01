using UnityEngine;
using System.Runtime.InteropServices;

public class Svr
{
    [DllImport ("libSvr")] 
    private static extern float RoomLobby ();
}