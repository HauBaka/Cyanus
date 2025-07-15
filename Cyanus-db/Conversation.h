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
	ll createdDate;
	string& name;
public:
	Conversation(User* owner, string& name);

	void sendMessage(Message* message);
	void removeMessage(Message* message);

	void addMember(User* user);
	void removeMember(User* user);

	ll getCreatedDate() {
		return this->createdDate;
	}
	~Conversation();
};
#endif 
