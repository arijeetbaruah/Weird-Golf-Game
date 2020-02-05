#pragma once
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <enet/enet.h>

class NetworkBase
{
public:
	NetworkBase();
	~NetworkBase();

	static int Initialise();
	static void Destroy();

	static int GetDefaultPort() { return 1234; }
protected:
	ENetHost* netHandle;
};

