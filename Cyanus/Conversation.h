#ifndef _CONVERSATION_H
#define _CONVERSATION_H

#include <string>
#include <iostream>
#include "AVLTree.h"
#include "User.h"
#include "Message.h"
#define ll long long
using namespace std;

class Conversation {
private:
	AVLTree<User*, string> members; //User - username
	AVLTree<Message*, ll> messages; // Message - ll (~ ID)
	ll id;
	string name;
public:
	Conversation(const string& name, ll id);
	string& getName();
	ll getID();
	string& getInfo();
	
	AVLTree<User*, string>& getMembers();
	AVLTree<Message*, ll>& getMessages();
};

#endif // _CONVERSATION_H