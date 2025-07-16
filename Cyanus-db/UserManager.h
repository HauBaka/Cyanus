#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_
#include "AVLTree.h"
#include "User.h"
#include <string>
#include <ios>
class UserManager {
private:
	AVLTree<User*, string> userDB; // User* - username
	AVLTree<string, string> tokenDB; // username - token
	bool checkPassword(User* user, const string& password);
public:
	User* getUser(const string& username);
	bool registerUser(const string& username, const string& displayName, const string& password);
	void removeUser(const string& username);
	bool login(const string& username, const string& password);
	string& getToken(const string& username);
	string& generateNewToken(const string& username);
	void addUser(User* user);
	AVLTree<string, string>& getTokenDatabase();
	AVLTree<User*, string>& getUserDatabase();
};
#endif