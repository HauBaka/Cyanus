#ifndef _CYANUS_HANDLE_H_
#define _CYANUS_HANDLE_H_

#include "CyanusDB.h"
#include <unordered_map>

#include <winsock2.h> 

enum REQUEST_TYPE {
	REGISTER,//username;displayName;password
	LOGIN,//username;password
	LOGOUT,//token
	DELETE_ACCOUNT,//token

	CHANGE_PASSWORD,//token;oldPassword;newPassword
	CHANGE_DISPLAY_NAME,//token;newDisplayName
	CHANGE_USERNAME,// owner;newUsername
	CHANGE_STATUS,// owner;status

	GET_USER_INFO,//username

	CREATE_CONVERSATION,// owner;conversationName
	DELETE_CONVERSATION,// owner;conversationID
	INVITE_TO_CONVERSATION,// owner;conversationID;username
	REQUEST_TO_JOIN_CONVERSATION,// user;conversationID
	ACCEPT_CONVERSATION_INVITATION,// user;conversationID
	ACCEPT_CONVERSATION_REQUEST,// owner;conversationID;username
	LEAVE_CONVERSATION,// user;conversationID

	SEND_MESSAGE,// sender;conversationID;message
	EDIT_MESSAGE,// sender;conversationID;messageID;newMessage
	DELETE_MESSAGE,// sender;conversationID;messageID

	GET_CONVERSATION_INFO,// conversationID
};

class CyanusHandle {
private:
	//CyanusDB& db;
	int port;

	SOCKET serverSocket; 
	bool running;         
public:
	CyanusHandle(const int port);
	~CyanusHandle();
	bool start(const int port);
	bool start();
	bool stop();

	void handleClient(SOCKET clientSocket);

	vector<string> parseRawRequest(const string& request);
	void handleParsedRequest(SOCKET clientSocket, vector<string>& args);
};


const unordered_map<string, REQUEST_TYPE> stringToRequestType = {  
    {"REGISTER", REGISTER},  
    {"LOGIN", LOGIN},  
    {"LOGOUT", LOGOUT},  
    {"DELETE_ACCOUNT", DELETE_ACCOUNT},  
    {"CHANGE_PASSWORD", CHANGE_PASSWORD},  
    {"CHANGE_DISPLAY_NAME", CHANGE_DISPLAY_NAME},  
    {"CHANGE_USERNAME", CHANGE_USERNAME},  
    {"CHANGE_STATUS", CHANGE_STATUS},  
    {"GET_USER_INFO", GET_USER_INFO},  
    {"CREATE_CONVERSATION", CREATE_CONVERSATION},  
    {"DELETE_CONVERSATION", DELETE_CONVERSATION},  
    {"INVITE_TO_CONVERSATION", INVITE_TO_CONVERSATION},  
    {"REQUEST_TO_JOIN_CONVERSATION", REQUEST_TO_JOIN_CONVERSATION},  
    {"ACCEPT_CONVERSATION_INVITATION", ACCEPT_CONVERSATION_INVITATION},  
    {"ACCEPT_CONVERSATION_REQUEST", ACCEPT_CONVERSATION_REQUEST},  
    {"LEAVE_CONVERSATION", LEAVE_CONVERSATION},  
    {"SEND_MESSAGE", SEND_MESSAGE},  
    {"EDIT_MESSAGE", EDIT_MESSAGE},  
    {"DELETE_MESSAGE", DELETE_MESSAGE},  
    {"GET_CONVERSATION_INFO", GET_CONVERSATION_INFO}  
};
#endif
