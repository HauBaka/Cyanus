#include "User.h"
User::User(const string& username, const string& displayName)
	: username(username), displayName(displayName) {
}
const string& User::getUsername() const {
	return username;
}
const string& User::getDisplayName() const {
	return displayName;
}
void User::setDisplayName(const string& newDisplayName) {
	displayName = newDisplayName;
}