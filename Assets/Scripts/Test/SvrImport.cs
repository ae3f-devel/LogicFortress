using System.Runtime.InteropServices;
using UnityEngine;

namespace Test
{
    public class SvrImport : MonoBehaviour
    {
        [DllImport("libSvrUDP", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SvrTest();
        public void Awake()
        {
            int a = 0;
	    a = SvrTest();

            Debug.Log($"DLL IMPORT TEST: {a}");
        }
    }
}
