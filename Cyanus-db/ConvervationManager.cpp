#include "ConversationManager.h"

void ConversationManager::createConversation(User* owner) {
	string roomName = owner->getDisplayName() + "'s room";
	Conversation* conversation = new Conversation(owner, roomName);
	auto node = conversationDB.createNode(conversation, conversation->getCreatedDate());
	conversationDB.add(node);
}

Conversation* ConversationManager::getConversation(const ll& id) {
	return conversationDB.findNodeByKey(id)->data;
}

void ConversationManager::removeConversation(const ll& id) {
	conversationDB.remove(id);	
}

ConversationManager::~ConversationManager() {
	//Todo: clear conversations file, for each conversation, write it to file. 
	//then remove all pointers.
}