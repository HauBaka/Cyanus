#define _HAS_STD_BYTE 0
#include "CyanusHandle.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")  
CyanusHandle::CyanusHandle(CyanusDB& database, const int port) : db(database), port(port) {}

CyanusHandle::~CyanusHandle() {
    stop();
    std::cout << "[CyanusDB] Server stopped.\n";
	WSACleanup(); 
}

bool CyanusHandle::start() {
	return start(port); // Default port
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
		vector<string> args = parseRawRequest(request);
        if (args.empty()) {
            std::cerr << "Failed to parse request: " << request << "\n";
            string response = "400;Invalid request format!\n";
            send(clientSocket, response.c_str(), response.size(), 0);
            continue;
        }
		// Handle the parsed request
		handleParsedRequest(clientSocket, args);
    }
}

vector<string> CyanusHandle::parseRawRequest(const string& request) {

	vector<string> args;
    if (request.empty()) {
        std::cerr << "Received empty request.\n";
        return args;
	}
	int prevPos = 0, curPos = request.find(';');
    while (curPos != string::npos) {
        args.push_back(request.substr(prevPos, curPos - prevPos));
        prevPos = curPos + 1;
        curPos = request.find(';', prevPos);
	}
    args.push_back(request.substr(prevPos)); // Add the last part after the last semicolon
    if (args.empty()) {
        std::cerr << "Parsed request is empty.\n";
        return args;
	}
    if (args.size() < 2) {
        std::cerr << "Invalid request format. Expected at least 2 parts.\n";
        return args;
    }
	std::cout << "[CyanusDB] Received request: " << request << "\n";
    return args;
}

void CyanusHandle::handleParsedRequest(SOCKET clientSocket, vector<string>& args)
{

    string response;
    if (args.empty()) {
        std::cerr << "No arguments provided for request handling.\n";
		response = "400;No arguments provided!\n";
		send(clientSocket, response.c_str(), response.size(), 0);
        return;
	}
    if (!stringToRequestType.count(args[0])) {
        std::cerr << "Unknown request type: " << args[0] << "\n";
        response = "400;Unknown request type!\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }

	REQUEST_TYPE type = stringToRequestType.at(args[0]);
    string username, displayName, password, token, oldPassword, newPassword, newDisplayName, newUsername, status, message, newMessage, inviteUsername, requesterUsername, conversationName;
    ll conversationID = 0, messageID = 0;
	switch (type) {
	case REGISTER:
		if (args.size() != 4) {
			response = "400;Invalid request format!\n";
			std::cerr << response;
			send(clientSocket, response.c_str(), response.size(), 0);
			return;
		}
		username = args[1];
		displayName = args[2];
		password = args[3];
		if (!db.userManager().registerUser(username, displayName, password)) {
			response = "406;User with this username is existed!\n";
		}
		else {
			//Send success response with token
			token = db.userManager().getToken(username);
			response = "200;" + token + "\n";
		}
		break;

	case LOGIN:
		if (args.size() != 3) {
			response = "400;Invalid request format!\n";
			std::cerr << response;
			send(clientSocket, response.c_str(), response.size(), 0);
			return;
		}
		username = args[1];
		password = args[2];
		if (db.userManager().login(username, password)) {
			//Generate a new token for the user
			db.userManager().generateNewToken(username);
			//Send success response with token
			response = "200;" + db.userManager().getToken(username) + "\n";
		}
		else {
			response = "401;Invalid username or password!\n";
		}
		break;

	case LOGOUT:
		if (args.size() != 2) {
			response = "400;Invalid request format!\n";
			std::cerr << response;
			send(clientSocket, response.c_str(), response.size(), 0);
			return;
		}
		token = args[1];
		if (db.userManager().logout(token)) {
			response = "200;Logout successful!\n";
		}
		else {
			response = "401;Invalid token!\n";
		}
		break;

	case DELETE_ACCOUNT:
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        if (db.userManager().deleteAccount(token)) {
            response = "200;Account deleted successfully!\n";
        }
        else {
            response = "401;Invalid token!\n";
        }
		break;
	case CHANGE_PASSWORD:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        oldPassword = args[2];
        newPassword = args[3];
        if (db.userManager().changePassword(token, oldPassword, newPassword)) {
            response = "200;Password changed successfully!\n";
        }
        else {
            response = "401;Invalid token or password!\n";
        }
		break;
    case CHANGE_DISPLAY_NAME:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        newDisplayName = args[2];
        if (db.userManager().changeDisplayName(token, newDisplayName)) {
            response = "200;Display name changed successfully!\n";
        }
        else {
            response = "401;Invalid token!\n";
		}
		break;
     
    case CHANGE_USERNAME:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        newUsername = args[2];
        if (db.userManager().changeUsername(token, newUsername)) {
            response = "200;Username changed successfully!\n";
        }
        else {
			response = "401;Invalid token or username already exists!\n";
		}
		break;
	case CHANGE_STATUS:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        status = args[2];
        if (db.userManager().changeStatus(token, status)) {
            response = "200;Status changed successfully!\n";
        }
        else {
            response = "401;Invalid token!\n";
        }
		break;
	case GET_USER_INFO:
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        username = args[1];
        User* user = db.userManager().getUser(username);
        if (user) {
            response = "200;" + user->getUserName() + ";" + user->getDisplayName() + ";" + user->getStatus() + "\n";
        }
        else {
            response = "404;User not found!\n";
        }
		break;
        
    case CREATE_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationName = args[2];
        conversationID = db.conversationManager().createConversation(token, conversationName);
        if (conversationID != -1) {
            response = "200;" + std::to_string(conversationID) + "\n";
        }
        else {
            response = "401;Invalid token or conversation name already exists!\n";
		}
		break;

    case DELETE_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        if (db.conversationManager().deleteConversation(token, conversationID)) {
            response = "200;Conversation deleted successfully!\n";
        }
        else {
			response = "401;Invalid token or conversation ID!\n";
		}
		break;
    case INVITE_TO_CONVERSATION:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        inviteUsername = args[3];
        if (db.conversationManager().inviteToConversation(token, conversationID, inviteUsername)) {
            response = "200;Invitation sent successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID or user not found!\n";
		}
		break;
    case REQUEST_TO_JOIN_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        if (db.conversationManager().requestToJoinConversation(token, conversationID)) {
            response = "200;Request to join conversation sent successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID!\n";
		}
        break;
    case ACCEPT_CONVERSATION_INVITATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        if (db.conversationManager().acceptConversationInvitation(token, conversationID)) {
            response = "200;Invitation accepted successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID!\n";
		}
        break;
    case ACCEPT_CONVERSATION_REQUEST:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        requesterUsername = args[3];
        if (db.conversationManager().acceptConversationRequest(token, conversationID, requesterUsername)) {
            response = "200;Request accepted successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID or user not found!\n";
		}
        break;
    case LEAVE_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        if (db.conversationManager().leaveConversation(token, conversationID)) {
            response = "200;Left conversation successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID!\n";
		}
        break;
    case SEND_MESSAGE:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        message = args[3];
        if (db.conversationManager().sendMessage(token, conversationID, message)) {
            response = "200;Message sent successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID!\n";
		}
        break;
    case EDIT_MESSAGE:
        if (args.size() != 5) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        messageID = std::stoll(args[3]);
        newMessage = args[4];
        if (db.conversationManager().editMessage(token, conversationID, messageID, newMessage)) {
            response = "200;Message edited successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID or message ID!\n";
        }
        break;
    case DELETE_MESSAGE:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        token = args[1];
        conversationID = std::stoll(args[2]);
        messageID = std::stoll(args[3]);
        if (db.conversationManager().deleteMessage(token, conversationID, messageID)) {
            response = "200;Message deleted successfully!\n";
        }
        else {
            response = "401;Invalid token or conversation ID or message ID!\n";
		}
        break;
    case GET_CONVERSATION_INFO:
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        conversationID = std::stoll(args[1]);
        Conversation* conversation = db.conversationManager().getConversation(conversationID);
        if (conversation) {
            response = "200;" + conversation->getInfo() + "\n"; // Assuming getInfo() returns a string with conversation details
        }
        else {
            response = "404;Conversation not found!\n";
		}
		break;
	default:
		response = "400;Unknown request type!\n";
		std::cerr << response;
		break;
	}

	send(clientSocket, response.c_str(), response.size(), 0);
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
