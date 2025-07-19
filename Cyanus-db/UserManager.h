#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_
#include "AVLTree.h"
#include "User.h"
#include "Conversation.h"
#include <string>
#include <ios>
#define ll long long
class UserManager {
private:
	AVLTree<User*, string> userDB; // User* - username
	AVLTree<string, string> tokenDB; // username - token
	AVLTree<
		AVLTree<Conversation*, ll>, // conversation* - conversationID
		string> 
		conversationDB; // conversation tree - username 
	bool checkPassword(User* user, const string& password);
public:
	User* getUserByName(const string& username);
	User* getUserByToken(const string& token);
	bool registerUser(const string& username, const string& displayName, const string& password);
	bool removeUser(User* user);
	bool login(const string& username, const string& password);
	string& getToken(const string& username);
	string& generateNewToken(const string& username);
	void addUser(User* user);
	AVLTree<string, string>& getTokenDatabase();
	AVLTree<User*, string>& getUserDatabase();
	AVLTree<AVLTree<Conversation*, ll>, string>& getConversationDatabase();
	bool logout(User* user);
	bool changePassword(User* user, const string& oldPass, const string& newPass);
	bool changeDisplayName(User* user, const string& newDisplayName);
	bool changeUserName(User* user, const string& newUsername);
	bool changeStatus(User* user, const string& status);
};
#endif