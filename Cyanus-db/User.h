#ifndef _USER_H_
#define _USER_H_
#include <string>
#include <iostream>
using namespace std;
#define ll long long

class User {
private:
	string userName, displayName;
	string password, token;
	ll firstLogin, lastLogin;
public:
	string getName();
	string getDisplayName();
	string getHashedPassword();
	ll getFirstLogin();
	ll getLastLogin();
};
#endif