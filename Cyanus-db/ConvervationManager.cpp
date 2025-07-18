#include "ConversationManager.h"
#include "Utils.h"
void ConversationManager::createConversation(User* owner) {
	string roomName = owner->getDisplayName() + "'s room";
	ll currentTime = Utils::getCurrentTime();
	Conversation* conversation = new Conversation(owner, roomName, currentTime);
	addConversation(conversation);
}
void ConversationManager::addConversation(Conversation* conversation) {
	auto node = conversationDB.createNode(conversation, conversation->getID());
	conversationDB.add(node);
}
Conversation* ConversationManager::getConversation(const ll& id) {
	return conversationDB.findNodeByKey(id)->data;
}

void ConversationManager::removeConversation(const ll& id) {
	conversationDB.remove(id);	
}

AVLTree<Conversation*, ll>& ConversationManager::getConversationDatabase() {
	return conversationDB;
}

ConversationManager::~ConversationManager() {
	//Todo: clear conversations file, for each conversation, write it to file. 
	//then remove all pointers.
}