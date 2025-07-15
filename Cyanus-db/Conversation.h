#ifndef _CONVERSATION_H_
#define _CONVERSATION_H_
#include "AVLTree.h"
#include "User.h"
#include "Message.h"
#include <string>
using namespace std;
#define ll long long
class Conversation {
private:
	User* owner;
	AVLTree<User*, string> members; //User - username
	AVLTree<Message*, ll> messages; // Message - ll (~ timestamp)
public:
	bool sendMessage(Message* message);
	bool removeMessage(Message* message);

	bool addMember(User* user);
	bool removeMember(User* user);
};
#endif 
