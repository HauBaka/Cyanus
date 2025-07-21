#ifndef _COMMAND_PROCESSOR_H_
#define _COMMAND_PROCESSOR_H_
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
enum REQUEST_TYPE {
	REGISTER,//username;displayName;password
	LOGIN,//username;password
	LOGOUT,//token
	DELETE_ACCOUNT,//token

	CHANGE_PASSWORD,//token;oldPassword;newPassword
	CHANGE_DISPLAY_NAME,//token;newDisplayName
	CHANGE_USERNAME,// owner's token;newUsername
	CHANGE_STATUS,// owner's token;status

	GET_USER_INFO,//user's token, target username

	CREATE_CONVERSATION,// owner's token;conversationName
	DELETE_CONVERSATION,// owner's token;conversationID
	INVITE_TO_CONVERSATION,// owner's token;conversationID;username
	REQUEST_TO_JOIN_CONVERSATION,// user's token;conversationID
	ACCEPT_CONVERSATION_INVITATION,// user's token;conversationID
	ACCEPT_CONVERSATION_REQUEST,// owner's token;conversationID;username
	LEAVE_CONVERSATION,// user's token;conversationID

	SEND_MESSAGE,// sender's token;conversationID;message
	EDIT_MESSAGE,// sender's token;conversationID;messageID;newMessage
	DELETE_MESSAGE,// sender's token;conversationID;messageID

	GET_CONVERSATION_INFO,// conversationID
};
class CommandProcessor {
private:
	CommandProcessor() = default; // Private constructor to prevent instantiation
	CommandProcessor(const CommandProcessor&) = delete; // Prevent copy construction
	CommandProcessor& operator=(const CommandProcessor&) = delete; // Prevent assignment
	CommandProcessor(CommandProcessor&&) = delete; // Prevent move construction
	CommandProcessor& operator=(CommandProcessor&&) = delete; // Prevent move assignment
	~CommandProcessor() = default; // Private destructor to prevent deletion

public:
	static CommandProcessor& getInstance() {
		static CommandProcessor instance; // Guaranteed to be destroyed, instantiated on first use
		return instance;
	}

	static string processCommand(vector<string>& args);
	static vector<string>& parseRawResponse(string& response);
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