using System.Runtime.InteropServices;
using UnityEngine;

public class TestAttr : MonoBehaviour
{
    [DllImport("liblibCli", CharSet = CharSet.Ansi)]
    public static extern void Test(out int a);
    public void Awake()
    {
        int a = 5;
        Test(out a);

        Debug.Log($"DLL IMPORT TEST: {a}");
    }
}