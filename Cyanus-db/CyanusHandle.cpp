#define _HAS_STD_BYTE 0
#include "CyanusHandle.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")  
CyanusHandle::CyanusHandle(CyanusDB& database) : db(database), port(6969) {}

CyanusHandle::~CyanusHandle() {
    stop();
    std::cout << "[CyanusDB] Server stopped.\n";
	WSACleanup(); 
}

bool CyanusHandle::start() {
	return start(6969); // Default port
}

bool CyanusHandle::start(const int port) {
    this->port = port;

    // 1. Init Winsock
    WSADATA wsaData;
    int wsaInit = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaInit != 0) {
        std::cerr << "WSAStartup failed: " << wsaInit << std::endl;
        return false;
    }

    // 2. Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed! Code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // 3. Bind
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed! Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    // 4. Listen
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed! Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    running = true;
    std::cout << "[CyanusDB] Server is running on port " << port << "...\n";

    // 5. Loop accept client
    while (running) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed! Code: " << WSAGetLastError() << std::endl;
            continue;
        }

		// 6. Create a new thread to handle the client
        thread([this, clientSocket]() {
            this->handleClient(clientSocket);
            closesocket(clientSocket);
            }).detach();
    }

    return true;
}

void CyanusHandle::handleClient(SOCKET clientSocket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        std::string request(buffer);
		processRequest(clientSocket, request);
    }
}

void CyanusHandle::processRequest(SOCKET clientSocket, const string& request) {
	int pos_1 = request.find(';'), 
        pos_2 = request.find(';', pos_1 + 1), 
        pos_3 = request.find(';', pos_2 + 1);
	string category = request.substr(0, request.find(';'));
    if (category == "LOGIN") {
        string username = request.substr(pos_1 + 1, pos_2 - pos_1 - 1);
        string password = request.substr(pos_2 + 1, pos_3 - pos_2 - 1);
		string response = "401;Invalid username or password!\n";
		cout << username << " " << password << endl;
        if (db.userManager().login(username, password)) {
			db.userManager().generateNewToken(username);
            response = "200;" + db.userManager().getToken(username) +"\n";
        }

        send(clientSocket, response.c_str(), response.size(), 0);

    } else if (category == "REGISTER") {
		string username = request.substr(pos_1 + 1, pos_2 - pos_1 - 1);
		string password = request.substr(pos_2 + 1, pos_3 - pos_2 - 1);
		string displayName = request.substr(pos_3 + 1);
		cout << username << " " << password << " " << displayName << endl;
		string response = "";

        if (!db.userManager().registerUser(username, password, displayName)) {
           response = "406;User with this username is existed!\n";
        }
        else {
            string token = db.userManager().generateNewToken(username);
			response = "200;" + token + "\n";
        }

        send(clientSocket, response.c_str(), response.size(), 0);

    } else {
		string response = "400;Unknown request category: " + category + "\n";
        std::cerr << response;
        send(clientSocket, response.c_str(), response.size(), 0);
	}
}

bool CyanusHandle::stop() {
    running = false;
    closesocket(serverSocket);
    WSACleanup();
    return true;
}


CyanusDB& CyanusHandle::getDB() {
	return db;
}
