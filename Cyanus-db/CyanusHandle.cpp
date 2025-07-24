#define _HAS_STD_BYTE 0
#include "CyanusHandle.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <iostream>
#include "CyanusCore.h"
#pragma comment(lib, "ws2_32.lib")  
CyanusHandle::CyanusHandle(const int port) : port(port) {}

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
            //closesocket(clientSocket);
            }).detach();
    }

    return true;
}

void CyanusHandle::handleClient(SOCKET clientSocket) {
    char buffer[1024];
	cout << "[CyanusDB] A client connected.\n";
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
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
	std::cout << "[CyanusDB] A client disconnected.\n";
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

    UserManager& userMng = CyanusCore::getInstance().getDB().userManager();
    ConversationManager& conversationMng = CyanusCore::getInstance().getDB().conversationManager();
	
    User* user, *owner;
    Conversation* conversation;

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
		if (!userMng.registerUser(username, displayName, password)) {
			response = "406;User with this username is existed!\n";
            send(clientSocket, response.c_str(), response.size(), 0);

		}
		else {
			//Send success response with token
			User* newUser = userMng.getUserByName(username);
			response = "200;" + newUser->getToken() + "\n";

			newUser->getUserSocket().setClientSocket(clientSocket);

			newUser->getUserSocket().sendResponse(response);

			std::cout << "[CyanusDB] User registered: " << username << "\n";
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
		if (userMng.login(username, password)) {
			//Generate a new token for the user
			userMng.generateNewToken(username);
			User* user = userMng.getUserByName(username);
			//Send success response with token
			response = "200;" + user->getToken() + "\n";

			user->getUserSocket().setClientSocket(clientSocket);
			user->getUserSocket().sendResponse(response);
		}
		else {
			response = "401;Invalid username or password!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
		break;

	case LOGOUT:
		if (args.size() != 2) {
			response = "400;Invalid request format!\n";
			std::cerr << response;
			send(clientSocket, response.c_str(), response.size(), 0);
			return;
		}
        user = userMng.getUserByToken(args[1]);
		if (user && userMng.logout(user)) {
            response = "200;Logged out successfully!\n";
			user->getUserSocket().sendResponse(response);
			user->getUserSocket().setClientSocket(INVALID_SOCKET); 
        }
        else {
            response = "401;Invalid token!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
		break;

	case DELETE_ACCOUNT:
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
		user = userMng.getUserByToken(args[1]);
        if (user && userMng.removeUser(user)) {
            response = "200;Account deleted successfully!\n";
			user->getUserSocket().sendResponse(response);
			delete user; 

        }
        else {
            response = "401;Invalid token!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
        break;
	case CHANGE_PASSWORD:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        user = userMng.getUserByToken(args[1]);
        oldPassword = args[2];
        newPassword = args[3];
        if (user && userMng.changePassword(user, oldPassword, newPassword)) {
            response = "200;Password changed successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token or password!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
        }
        break;
    case CHANGE_DISPLAY_NAME:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        user = userMng.getUserByToken(args[1]);
        newDisplayName = args[2];
        if (user && userMng.changeDisplayName(user, newDisplayName)) {
            response = "200;Display name changed successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token or display name!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
		break;
     
    case CHANGE_USERNAME:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        user = userMng.getUserByToken(args[1]);
        newUsername = args[2];
        if (user && userMng.changeUserName(user, newUsername)) {
            response = "200;Username changed successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token or username existed!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
		break;
	case CHANGE_STATUS:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        user = userMng.getUserByToken(args[1]);
        status = args[2];
        if (user && userMng.changeStatus(user, status)) {
            response = "200;Status changed successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token or status!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
        }
		break;
	case GET_USER_INFO://TODO: Implement it again, this one expired
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        user = userMng.getUserByName(args[1]);
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

		owner = userMng.getUserByToken(args[1]);
        conversationName = args[2];
        if (owner) {
            ll conversationID = conversationMng.createConversation(owner, conversationName);
            response = "200;" + to_string(conversationID) + "\n";
			owner->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}

		break;

    case DELETE_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }

		owner = userMng.getUserByToken(args[1]);
        conversationID = std::stoll(args[2]);

        if (owner && conversationMng.deleteConversation(owner, conversationID)) {
            response = "200;Conversation deleted successfully!\n";
			owner->getUserSocket().sendResponse(response);
        }
        else {
			response = "401;Invalid token or conversation ID!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
		break;
    case LEAVE_CONVERSATION:
        if (args.size() != 3) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
		user = userMng.getUserByToken(args[1]);

        conversationID = std::stoll(args[2]);
        if (user && conversationMng.leaveConversation(user, conversationID)) {
            response = "200;Left conversation successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token or conversation ID!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
		}
        break;
    case SEND_MESSAGE:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
		user = userMng.getUserByToken(args[1]);
        conversationID = std::stoll(args[2]);
        message = args[3];
        if (user) {
			messageID = conversationMng.sendMessage(user, conversationID, message);
              if (messageID != -1) {
                    response = "200;" + std::to_string(messageID) + "\n";
                }
                else {
                    response = "404;Conversation not found!\n";
		      }
			  user->getUserSocket().sendResponse(response);
        }
        else {
			response = "401;Invalid token or conversation ID!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
        }
		break;
    case EDIT_MESSAGE:
        if (args.size() != 5) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }

		user = userMng.getUserByToken(args[1]);
		conversationID = std::stoll(args[2]);
		messageID = std::stoll(args[3]);
		newMessage = args[4];

        if (user && conversationMng.editMessage(user, conversationID, messageID, newMessage)) {
            response = "200;Message edited successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
			response = "401;Invalid token or conversation ID or message ID!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
        }
		break;
    case DELETE_MESSAGE:
        if (args.size() != 4) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }

        user = userMng.getUserByToken(args[1]);
        conversationID = std::stoll(args[2]);
        messageID = std::stoll(args[3]);
        
        if (user && conversationMng.deleteMessage(user, conversationID, messageID)) {
            response = "200;Message deleted successfully!\n";
			user->getUserSocket().sendResponse(response);
        }
        else {
            response = "401;Invalid token, conversation ID, or message ID!\n";
			send(clientSocket, response.c_str(), response.size(), 0);
        }
        break;
	case GET_CONVERSATION_INFO://TODO: Implement it again, this one expired
        if (args.size() != 2) {
            response = "400;Invalid request format!\n";
            std::cerr << response;
            send(clientSocket, response.c_str(), response.size(), 0);
            return;
        }
        conversationID = std::stoll(args[1]);
        conversation = conversationMng.getConversation(conversationID);
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
		send(clientSocket, response.c_str(), response.size(), 0);
		break;
	}
}

bool CyanusHandle::stop() {
    running = false;
    closesocket(serverSocket);
    WSACleanup();
    return true;
}

