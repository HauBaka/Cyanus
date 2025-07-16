#ifndef _CONVERSATION_H_
#define _CONVERSATION_H_
#include "AVLTree.h"
#include "User.h"
#include "Message.h"
#include <fstream>
#include <string>
using namespace std;
#define ll long long
class Conversation {
private:
	User* owner;
	AVLTree<User*, string> members; //User - username
	AVLTree<Message*, ll> messages; // Message - ll (~ timestamp)
	ll& createdDate;
	string name;

	void writeString(ofstream& ofs, const string& s);
public:
	Conversation(User* owner, string& name, ll& createdDate);

	void sendMessage(Message* message);
	void addMessage(Message* message);
	void removeMessage(Message* message);

	void addMember(User* user);
	void addNewMember(User* user);
	void removeMember(User* user);

	string& getName();
	ll getCreatedDate() {
		return this->createdDate;
	}

	void save(ofstream& ofs);

	~Conversation();
};


#endif 
