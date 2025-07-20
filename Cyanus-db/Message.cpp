#include "Message.h"
#include "Utils.h"

Message::Message(User* sender, const string& message) {
	this->sender = sender;
	this->message = message;
	this->id = Utils::getCurrentTime();
	this->edited = false;

	auto node = editions.createNode(this->message, this->id);
	editions.add(node);
}

Message::Message(User* sender, const string& message, ll createdDate) {
	this->sender = sender;
	this->message = message;
	this->id = createdDate;
	this->edited = false;
	auto node = editions.createNode(this->message, this->id);
	editions.add(node);
}

User* Message::getSender() {
	return sender;
}

AVLTree<string, ll>& Message::getEditions() {
	return this->editions;
}

string& Message::getMessage() {
	return message;
}

void Message::change(const string& s) {
	this->message = s;
	auto node = editions.createNode(this->message, Utils::getCurrentTime());
	editions.add(node);
	this->edited = true;
}

ll Message::getID()  {
	return id;
}


Message::~Message() {
}