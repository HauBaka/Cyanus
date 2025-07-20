#define _HAS_STD_BYTE 0
#include "ConversationManager.h"
#include "Utils.h"
#include "UserManager.h"
ll ConversationManager::createConversation(User* owner) {
	string roomName = owner->getDisplayName() + "'s room";
	ll currentTime = Utils::getCurrentTime();
	Conversation* conversation = new Conversation(owner, roomName, currentTime);
	addConversation(conversation);
	return conversation->getID();
}
ll ConversationManager::createConversation(User* owner, string& name)
{
	
	string roomName = name;
	ll currentTime = Utils::getCurrentTime();
	Conversation* conversation = new Conversation(owner, roomName, currentTime);
	addConversation(conversation);
	return conversation->getID();
}
void ConversationManager::addConversation(Conversation* conversation) {
	auto node = conversationDB.createNode(conversation, conversation->getID());
	conversationDB.add(node);
}
Conversation* ConversationManager::getConversation(const ll& id) {
	return conversationDB.findNodeByKey(id)->data;
}

bool ConversationManager::editMessage(User* sender, const ll& ID, const ll& messageID, const string& newMessage)
{
	return false;
}

bool ConversationManager::inviteToConversation(User* owner, const ll& ID, User* user)
{
	return false;
}

bool ConversationManager::leaveConversation(User* user, const ll& ID)
{
	return false;
}

ll ConversationManager::sendMessage(User* sender, const ll& ID, const string& message)
{
	Conversation* conversation = getConversation(ID);
	if (!conversation) return -1; // Conversation not found


	Message* msg = new Message(sender, message, Utils::getCurrentTime());
	conversation->sendMessage(msg);
	return msg->getID(); // Return the message ID
}

bool ConversationManager::deleteMessage(User* sender, const ll& ID, const ll& messageID)
{
	return false;
}

void ConversationManager::deleteConversation(const ll& id) {
	conversationDB.remove(id);	
}

bool ConversationManager::deleteConversation(User* owner, const ll& ID)
{
	Conversation* conversation = getConversation(ID);
	if (!conversation) return false;
	if (conversation->getOwner()->getUserName() != owner->getUserName()) return false; // Only owner can delete the conversation
	deleteConversation(ID);
	return true;
}

AVLTree<Conversation*, ll>& ConversationManager::getConversationDatabase() {
	return conversationDB;
}

ConversationManager::~ConversationManager() {
	//Todo: clear conversations file, for each conversation, write it to file. 
	//then remove all pointers.
}