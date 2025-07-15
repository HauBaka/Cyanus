#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_
#include "AVLTree.h"
#include "User.h"
#include <string>
#include <ios>
class UserManager {
private:
	AVLTree<User*, string> userDB; // User* - username
	bool checkPassword(const User& user, const string& password);
public:
	User* getUser(const string& username);
	bool registerUser(const string& username, const string& displayName, const string& password);
	void removeUser(const string& username);
	bool login(const string& username, const string& password);
};
#endif