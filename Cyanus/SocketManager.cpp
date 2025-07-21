#include "SocketManager.h"
#include <thread>

SocketManager::SocketManager()
{
}

bool SocketManager::connectToServer(const std::string& ipAddress, int port)
{
    // 1. Init Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed: " << result << endl;
        return 1;
    }

    // 2. Create socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed! Code: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }
    
	//Keep the connection alive
    thread([this]() {
        keepConnectionAlive();
		}).detach();
}

void SocketManager::disconnect()
{
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
        WSACleanup();
    }
    else {
        cerr << "Socket is not connected!" << endl;
	}
}
//Return format: "status code;message"
string SocketManager::sendMessage(const std::string& message)
{
    if (clientSocket == INVALID_SOCKET) {
		return "0;Socket is not connected!";
    }
    // Send the message to the server
    int result = send(clientSocket, message.c_str(), message.size(), 0);
    if (result == SOCKET_ERROR) {
        return "0;Send failed";
    }
    // Receive the response from the server
    char buffer[512];
    result = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (result > 0) {
        buffer[result] = '\0'; // Null-terminate the received data
        return std::string(buffer);
    } else if (result == 0) {
        return "0;Connection closed by server.";
    } else {
        return "0;Receive failed";
	}
}

void SocketManager::keepConnectionAlive()
{
    while (true) {
        // Send a keep-alive message to the server
        std::string keepAliveMessage = "KEEP_ALIVE";
        if (send(clientSocket, keepAliveMessage.c_str(), keepAliveMessage.size(), 0) == SOCKET_ERROR) {
            cerr << "Failed to send keep-alive message: " << WSAGetLastError() << endl;
            break; // Exit the loop if sending fails
        }
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait for 3 seconds before sending the next keep-alive message
	}
}
