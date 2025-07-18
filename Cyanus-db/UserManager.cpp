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
/*
Add a new user to the user database, token database and conversation database.
*/
void UserManager::addUser(User* user) {
	userDB.add(
		userDB.createNode(user, user->getUserName())
	);

	//generateNewToken(user->getUserName()); -> only called when user logs in

	conversationDB.add(
		conversationDB.createNode(
			AVLTree<Conversation*, ll>(), 
			user->getUserName()
		)
	);

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
	
	string& oldtoken = user->getToken();
	if (!oldtoken.empty() && tokenDB.findNodeByKey(oldtoken)) {
		tokenDB.remove(oldtoken);
	}

	string token = Utils::generateToken();
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

AVLTree<AVLTree<Conversation*, ll>, string>& UserManager::getConversationDatabase() {
	return conversationDB;
}

