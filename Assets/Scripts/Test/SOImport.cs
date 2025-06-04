using System.Runtime.InteropServices;
using UnityEngine;

namespace Test
{
    internal class SOImport : MonoBehaviour
    {
        [DllImport("libCli", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Test(out int a);
        public void Awake()
        {
            int a = 5;
            Test(out a);

            Debug.Log($"DLL IMPORT TEST: {a}");
        }
    }
}
