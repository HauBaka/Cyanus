#include "User.h"
#include "Utils.h"
#include <fstream>
//Create a new user with username, display name and password
User::User(const string& userName, const string& displayName, const string& password) {
    this->userName = userName;
    this->displayName = displayName;
    this->hashedPassword = Utils::hashPassword(password);
    this->firstLogin = Utils::getCurrentTime();
    this->lastLogin = 0;
}
//Add user from file
User::User(const string& userName, const string& displayName, const string& hashedPassword, ll firstLogin, ll lastLogin, string& token) {
    this->userName = userName;
    this->displayName = displayName;
    this->hashedPassword = hashedPassword;
    this->firstLogin = firstLogin;
    this->lastLogin = lastLogin;
    this->token = token;
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

string& User::getToken()
{
    return token;
}

string& User::getStatus()
{
    string s;
    return s;
}

void User::setToken(const string& token)
{
    this->token = token;
	lastLogin = Utils::getCurrentTime(); 
}

void User::changeDisplayName(const string& newName) {
    displayName = newName;
}

void User::changeUsername(const string& newName)
{
    userName = newName;
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
    Utils::writeString(ofs, token);
    
    ofs.write(reinterpret_cast<char*>(&firstLogin), sizeof(firstLogin));
    ofs.write(reinterpret_cast<char*>(&lastLogin), sizeof(lastLogin));
}

void User::changePassword(const string& newPass)
{
    hashedPassword = Utils::hashPassword(newPass);
}
