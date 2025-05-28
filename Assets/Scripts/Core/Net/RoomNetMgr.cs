using Unity.Netcode;
using UnityEngine;

public class RoomNetMgr : NetworkManager {
    public override void OnServerConnect(NetworkConnection conn)
    {
        Debug.Log("Client connected: " + conn);
        base.OnServerConnect(conn);
    }

    public override void OnServerAddPlayer(NetworkConnection conn, short playerControllerId)
    {
        var player = Instantiate(playerPrefab, Vector3.zero, Quaternion.identity);
        NetworkServer.AddPlayerForConnection(conn, player, playerControllerId);
        Debug.Log("Player added for connection: " + conn);
    } 
}