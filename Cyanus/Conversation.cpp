#include "Conversation.h"
Conversation::Conversation(const string& name, ll id)
	: name(name), id(id) {
}

string& Conversation::getName() {
	return name;
}

ll Conversation::getID() {
	return id;
}
string& Conversation::getInfo() {
	static string info = "Conversation: " + name + " (ID: " + to_string(id) + ")";
	return info;
}
AVLTree<User*, string>& Conversation::getMembers() {
	return members;
}
AVLTree<Message*, ll>& Conversation::getMessages() {
	return messages;
}