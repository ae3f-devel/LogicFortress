using System.Runtime.InteropServices;
using UnityEngine;

namespace Tests
{
    internal class SvrImport : MonoBehaviour
    {
        [DllImport("libSvrUDP", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SvrTest();
        public void Awake()
        {
#if UNITY_EDITOR
            int a = 0;
            a = SvrTest();

            Debug.Log($"DLL IMPORT TEST: {a}");
#endif
        }
    }
}
