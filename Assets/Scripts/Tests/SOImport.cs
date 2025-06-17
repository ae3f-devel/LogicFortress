using System.Runtime.InteropServices;
using Unity.VisualScripting;
using UnityEditor.EditorTools;
using UnityEngine;

namespace Tests
{
    internal class SOImport : MonoBehaviour
    {
        [DllImport("libCli", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Test(out int a);
        public void Awake()
        {
#if UNITY_EDITOR
            int a = 5;
            Test(out a);
            Debug.Log($"DLL IMPORT TEST: {a}");
#endif
        }
    }
}
