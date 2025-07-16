#ifndef _CYANUSDB_
#define _CYANUSDB_
#include "AVLTree.h"
#include "UserManager.h"
#include "ConversationManager.h"
class CyanusDB {
private:
	//Database for users and conversations
	UserManager userMng;
	ConversationManager conversationMng;

	void saveUsers();
	void saveConversations();

	void readUsers();
	void readConversations();


public:
	UserManager& userManager();
	ConversationManager& conversationManager();

	void save();
	void load();

	~CyanusDB();
};
#endif