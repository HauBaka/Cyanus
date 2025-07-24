#ifndef _SOCKET_MANAGER_H_
#define _SOCKET_MANAGER_H_

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class SocketManager {
public:
    SocketManager();

    bool connectToServer(const std::string& ipAddress, int port);
    void disconnect();

    string sendMessage(const std::string message);

private:
    SOCKET clientSocket;
	void keepConnectionAlive();

};

#endif 
