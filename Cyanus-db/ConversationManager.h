#ifndef _CONVERSATIONMANAGER_H_
#define _HAS_STD_BYTE 0
#define _CONVERSATIONMANAGER_H_
#include "Conversation.h"
#include "AVLTree.h"
#define ll long long
class ConversationManager {
private:
	AVLTree<Conversation*, ll> conversationDB; //Conversation - ll(~created time)
public:
	ll createConversation(User* owner);
	ll createConversation(User* owner, string& name);
	void addConversation(Conversation* conversation);
	Conversation* getConversation(const ll& id);
	
	bool inviteToConversation(User* owner, const ll& ID, User* user);
	bool leaveConversation(User* user, const ll& ID);
	

	ll sendMessage(User* sender, const ll& ID, const string& message);
	bool editMessage(User* sender, const ll& ID, const ll& messageID, const string& newMessage);
	bool deleteMessage(User* sender, const ll& ID, const ll& messageID);

	void deleteConversation(const ll& id);
	bool deleteConversation(User* owner, const ll& ID);

	AVLTree<Conversation*, ll>& getConversationDatabase();

	~ConversationManager();
};
#endif