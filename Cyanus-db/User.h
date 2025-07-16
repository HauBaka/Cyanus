#ifndef _USER_H_
#define _USER_H_
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#define ll long long

class User {
private:
	string userName, displayName, hashedPassword, token;
	ll firstLogin, lastLogin;
public:
	User(const string& userName, const string& displayName, const string& password);
	User(const string& userName, const string& displayName, const string& hashedPassword, ll firstLogin, ll lastLogin, string& token);
	string& getUserName();
	string& getDisplayName();
	string& getHashedPassword() ;
	string& getToken();
	void setToken(const string& token);
	void changeDisplayName(const string& newName);
	ll getFirstLogin();
	ll getLastLogin();
	void save(ofstream& ofs);
};
#endif