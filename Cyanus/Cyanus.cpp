#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
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

    // 3. Setup server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6969); // phải trùng với port server
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // hoặc địa chỉ IP máy server

    // 4. Connect to server
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Connection failed! Code: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server!\n";
    while (true) {
		cout << "Enter message to send (or 'exit' to quit): ";
        string input;
        getline(cin, input);
        if (input == "exit") {
            break; // Thoát vòng lặp nếu người dùng nhập 'exit'
        }
        // Gửi dữ liệu
        send(clientSocket, input.c_str(), input.size(), 0);
        // Nhận phản hồi từ server
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "[Server] " << string(buffer, bytesReceived) << endl;
        } else {
            cerr << "Error receiving data from server!" << endl;
            break; // Thoát nếu có lỗi khi nhận dữ liệu
		}
    }

    // 7. Đóng kết nối
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
