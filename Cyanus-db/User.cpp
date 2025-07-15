#include "User.h"
#include "Utils.h"
User::User(const string& userName, const string& displayName, const string& password) {
    this->userName = userName;
    this->displayName = displayName;
    this->password = Utils::hashPassword(password);
    this->firstLogin = Utils::getCurrentTime();
    this->lastLogin = 0;
}

string User::getUserName() {
    return userName;
}

string User::getDisplayName() {
    return displayName;
}

string User::getHashedPassword() const {
    return hashedPassword;
}

void User::changeDisplayName(const string& newName) {
    displayName = newName;
}


ll User::getFirstLogin() {
    return firstLogin;
}

ll User::getLastLogin() {
    return lastLogin;
}