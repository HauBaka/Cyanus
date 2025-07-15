#include "Conversation.h"
#include "Utils.h"
Conversation::Conversation(User* owner, string& name) {
	this->owner = owner;
	this->name = name;
}

void Conversation::sendMessage(Message* message) {
	auto node = messages.createNode(message, Utils::getCurrentTime());
	messages.add(node);
	//send packet...
}

void Conversation::removeMessage(Message* message) {
	messages.remove(message->getSentDate());
	//send packet...
}

void Conversation::addMember(User* user) {
	auto node = members.createNode(user, user->getUserName());
	members.add(node);
	//send packet...
}

void Conversation::removeMember(User* user) {
	members.remove(user->getUserName());
	//send packet...
}

Conversation::~Conversation() {
	//Todo: save to file before remove trees.
}