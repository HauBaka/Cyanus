#define _HAS_STD_BYTE 0
#include "UserManager.h"

#include "Utils.h"
using namespace std;


bool UserManager::checkPassword(User* user, const string& password) {
	return user->getHashedPassword() == Utils::hashPassword(password);
}


User* UserManager::getUserByName(const string& username) {
	auto node = userDB.findNodeByKey(username);
	return node ? node->data : nullptr;
}

User* UserManager::getUserByToken(const string& token)
{
	auto node = tokenDB.findNodeByKey(token);
	if (node) {
		return getUserByName(node->data);
	}
	return nullptr;
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
bool UserManager::removeUser(User* user) {
	if (!user) return 0;
	string username = user->getUserName();
	//Remove user from userDB
	userDB.remove(username);
	//Remove token from tokenDB
	string token = user->getToken();
	if (!token.empty()) {
		tokenDB.remove(token);
	}
	//Remove user from their conversations
	vector<pair<Conversation*, ll>> conversations = conversationDB.findNodeByKey(user->getUserName())->data.getAllData(); // updated to use user->getUserName()
	
	for (const auto& conv : conversations) {
		Conversation* conversation = conv.first;
		if (conversation) {
			conversation->removeMember(user);
		}
	}
	return 1;
}

bool UserManager::login(const string& username, const string& password) {
	User* user = getUserByName(username);
	return user && checkPassword(user, password);
}

string& UserManager::getToken(const string& username)
{
	User* user = getUserByName(username);
	if (user) return user->getToken();
	throw std::runtime_error("User not found");
}

string& UserManager::generateNewToken(const string& username) {
	User* user = getUserByName(username);
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

bool UserManager::logout(User* user)
{
	if (!user) return 0;
	string token = user->getToken();
	if (token.empty()) return 0;
	//Remove token from tokenDB
	tokenDB.remove(token);
	//Clear user's token
	user->setToken("");
	return 1;
}

bool UserManager::changePassword(User* user, const string& oldPass, const string& newPass)
{
	if (!user || !checkPassword(user, oldPass)) return 0;
	//Change password
	user->changePassword(newPass);
	return 1;
}

bool UserManager::changeDisplayName(User* user, const string& newDisplayName)
{
	if (!user || newDisplayName.empty()) return 0;
	//Change display name
	user->changeDisplayName(newDisplayName);
	return 1;
}

bool UserManager::changeUserName(User* user, const string& newUsername)
{
	if (!user || newUsername.empty() || userDB.findNodeByKey(newUsername)) return 0;
	//Change username
	string oldUsername = user->getUserName();
	user->changeUserName(newUsername);
	//Update userDB
	userDB.remove(oldUsername);
	userDB.add(userDB.createNode(user, newUsername));
	//Update conversationDB
	auto convTreeNode = conversationDB.findNodeByKey(oldUsername);
	if (convTreeNode) {
		AVLTree<Conversation*, ll> convTree = convTreeNode->data;
		conversationDB.remove(oldUsername);
		conversationDB.add(conversationDB.createNode(convTree, newUsername));
	}
	return 1;
}

bool UserManager::changeStatus(User* user, const string& status)
{
	return false;
}

