#include "UserManager.h"

void UserManager::setToken(const string& token) {
	this->token = token;
}
void UserManager::setUsername(const string& username) {
	this->username = username;
}
void UserManager::setDisplayName(const string& displayName) {
	this->displayName = displayName;
}

const string& UserManager::getToken() const {
	return this->token;
}
const string& UserManager::getUsername() const {
	return this->username;
}
const string& UserManager::getDisplayName() const {
	return this->displayName;
}