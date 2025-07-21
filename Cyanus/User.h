#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
private:
    string username;
	string displayName;
public:
    User(const string& username, const string& displayName);
    const string& getUsername() const;
    const string& getDisplayName() const;
    void setDisplayName(const string& newDisplayName);
};

#endif // USER_H