#define _HAS_STD_BYTE 0
#include "UserSocket.h"
#include "Utils.h"
#include <thread>

UserSocket::UserSocket()
{
	clientSocket = INVALID_SOCKET; 
}

UserSocket::UserSocket(SOCKET clientSocket) {
	setClientSocket(clientSocket);
}

UserSocket::~UserSocket() {
	if (clientSocket != INVALID_SOCKET) {
		closesocket(clientSocket);
	}
}

SOCKET UserSocket::getClientSocket()  {
	return clientSocket;
}

void UserSocket::sendResponse(const string& response) {
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "[UserSocket] Invalid socket, cannot send response.\n";
		return;
	}
	int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
	if (bytesSent == SOCKET_ERROR) {
		std::cerr << "[UserSocket] Failed to send response. Error: " << WSAGetLastError() << "\n";
	}
	else {
		lastActiveTime = Utils::getCurrentTime(); 
	}
}

void UserSocket::setClientSocket(SOCKET socket)
{
	lastActiveTime = Utils::getCurrentTime(); 
	clientSocket = socket;

	thread([&]() {
		// Monitor the socket for inactivity
		while (true) {
			if (clientSocket == INVALID_SOCKET || Utils::getCurrentTime() - lastActiveTime > 3000) { // 3 seconds
				closesocket(clientSocket);
				clientSocket = INVALID_SOCKET;
				break;
			}
			Sleep(3000); // Check every 3 seconds
		}
	}).detach();
}

void UserSocket::setLastActiveTime(ll time)
{
	lastActiveTime = time;
}
