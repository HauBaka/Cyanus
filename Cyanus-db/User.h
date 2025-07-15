#ifndef _USER_H_
#define _USER_H_
#include <string>
#include <iostream>
using namespace std;
#define ll long long

class User {
private:
	string userName, displayName, hashedPassword;
	string password, token;
	ll firstLogin, lastLogin;
public:
	User(const string& userName, const string& displayName, const string& password);
	string getUserName();
	string getDisplayName();
	string getHashedPassword() const;
	void changeDisplayName(const string& newName);
	ll getFirstLogin();
	ll getLastLogin();
};
#endif