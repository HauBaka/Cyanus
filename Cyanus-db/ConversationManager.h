#ifndef _CONVERSATIONMANAGER_H_
#define _CONVERSATIONMANAGER_H_
#include "Conversation.h"
#include "AVLTree.h"
#define ll long long
class ConversationManager {
private:
	AVLTree<Conversation*, ll> conversationDB; //Conversation - ll(~created time)
public:
	ll createConversation(const User& owner);
	Conversation* getConversation(const ll& id);

	bool removeConversation(const ll& id);
};
#endif