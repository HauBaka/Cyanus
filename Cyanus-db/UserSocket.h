#ifndef _USER_SOCKET_H_
#define _USER_SOCKET_H_
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")  
#define ll long long
using namespace std;
class UserSocket {
private:
	SOCKET clientSocket;
	ll lastActiveTime; 
public:
	UserSocket();
	UserSocket(SOCKET clientSocket);
	~UserSocket();
	SOCKET getClientSocket();
	void sendResponse(const string& response);
	void setClientSocket(SOCKET socket);
	void setLastActiveTime(ll time);

};
#endif