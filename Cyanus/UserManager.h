#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include <string>
#include <iostream>
using namespace std;

class UserManager {
private:
	UserManager() = default;
	UserManager(const UserManager&) = delete;
	UserManager& operator=(const UserManager&) = delete;

	string token, username, displayName;
	
public:
	static UserManager& getInstance() {
		static UserManager instance;
		return instance;
	}
	void setToken(const string& token);
	void setUsername(const string& username);
	void setDisplayName(const string& displayName);
	const string& getToken() const;
	const string& getUsername() const;
	const string& getDisplayName() const;

};

#endif // _USERMANAGER_H