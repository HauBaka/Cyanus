#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include "User.h"
using namespace std;

class Message {
private:
    string content;
    User* sender;
    long long id;
public:
    Message(const string& content, User* sender, long long ID);
    string getContent() const;
    User* getSender() const;
    long long getID() const;
};

#endif // MESSAGE_H