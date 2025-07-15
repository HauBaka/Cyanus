#include "UserManager.h"

#include "Utils.h"
using namespace std;


bool UserManager::checkPassword(User* user, const string& password) {
	return user->getHashedPassword() == Utils::hashPassword(password);
}

User* UserManager::getUser(const string& username) {
	auto node = userDB.findNodeByKey(username);
	return node ? node->data : nullptr;
}

bool UserManager::registerUser(const string& username, const string& displayName, const string& password) {
	if (userDB.findNodeByKey(username)) return 0;
	User* user = new User(username, displayName, password);
	addUser(user);
	return 1;
}
void UserManager::addUser(User* user) {
	AVLTree<User*, string>::Node* node = userDB.createNode(user, user->getUserName());
	userDB.add(node);
}
void UserManager::removeUser(const string& username) {
	userDB.remove(username);
}

bool UserManager::login(const string& username, const string& password) {
	User* user = getUser(username);
	return user && checkPassword(user, password);
}

AVLTree<User*, string> UserManager::getUserDatabase() {
	return userDB;
}