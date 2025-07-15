#include "User.h"
#include "Utils.h"
#include <fstream>
User::User(const string& userName, const string& displayName, const string& password) {
    this->userName = userName;
    this->displayName = displayName;
    this->hashedPassword = Utils::hashPassword(password);
    this->firstLogin = Utils::getCurrentTime();
    this->lastLogin = 0;
}
User::User(const string& userName, const string& displayName, const string& hashedPassword, ll firstLogin, ll lastLogin) {
    this->userName = userName;
    this->displayName = displayName;
    this->hashedPassword = hashedPassword;
    this->firstLogin = firstLogin;
    this->lastLogin = lastLogin;
}
string& User::getUserName() {
    return userName;
}

string& User::getDisplayName() {
    return displayName;
}

string& User::getHashedPassword()  {
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

void User::save(ofstream& ofs) {
    Utils::writeString(ofs, userName);
    Utils::writeString(ofs, displayName);
    Utils::writeString(ofs, hashedPassword);
    
    ofs.write(reinterpret_cast<char*>(&firstLogin), sizeof(firstLogin));
    ofs.write(reinterpret_cast<char*>(&lastLogin), sizeof(lastLogin));
}