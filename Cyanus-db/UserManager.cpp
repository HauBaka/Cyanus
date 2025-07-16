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
AVLTree<string, string>& UserManager::getTokenDatabase()
{
	return tokenDB;
}
void UserManager::removeUser(const string& username) {
	userDB.remove(username);
}

bool UserManager::login(const string& username, const string& password) {
	User* user = getUser(username);
	return user && checkPassword(user, password);
}

string& UserManager::getToken(const string& username)
{
	User* user = getUser(username);
	if (user) return user->getToken();
	throw std::runtime_error("User not found");
}

string& UserManager::generateNewToken(const string& username) {
	User* user = getUser(username);
	if (!user) throw std::runtime_error("User not found");
	string token = Utils::generateToken();
	string& oldtoken = user->getToken();
	if (tokenDB.findNodeByKey(oldtoken)) {
		tokenDB.remove(oldtoken);
	}
	while(tokenDB.findNodeByKey(token)) {
		token = Utils::generateToken(); 
	}
	tokenDB.add(tokenDB.createNode(username, token));
	user->setToken(token);   
	return user->getToken();
}

AVLTree<User*, string>& UserManager::getUserDatabase() {
	return userDB;
}