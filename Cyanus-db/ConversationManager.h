#ifndef _CONVERSATIONMANAGER_H_
#define _CONVERSATIONMANAGER_H_
#include "Conversation.h"
#include "AVLTree.h"
#define ll long long
class ConversationManager {
private:
	AVLTree<Conversation*, ll> conversationDB; //Conversation - ll(~created time)
public:
	void createConversation(User* owner);
	void addConversation(Conversation* conversation);
	Conversation* getConversation(const ll& id);

	void removeConversation(const ll& id);

	AVLTree<Conversation*, ll>& getConversationDatabase();

	~ConversationManager();
};
#endif