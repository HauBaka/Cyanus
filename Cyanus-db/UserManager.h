#ifndef _USERMANAGER_H_
#define _USERMANAGER_H_
#include "AVLTree.h"
#include "User.h"
#include <string>
#include <ios>
class UserManager {
private:
	AVLTree<User*, string> userDB; // User - username
	string hashPassword(const string& password);
	bool checkPassword(const User& user, const string& password);
public:
	User* getUser(const string& username);

	bool registerUser(const string& name, const string& password);
	bool removeUser(const User& user);
	string login(const string& name, const string& password);

};
#endif