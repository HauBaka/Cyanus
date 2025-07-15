#include "Message.h"
#include "Utils.h"

Message::Message(const User& sender, const string& message) {
	this->sender = &sender;
	this->message = message;
	this->sentDate = Utils::getCurrentTime();
	this->edited = false;

	auto node = editions.createNode(this->message, this->sentDate);
	editions.add(node);
}

void Message::change(const string& s) {
	this->message = s;
	auto node = editions.createNode(this->message, Utils::getCurrentTime());
	editions.add(node);
	this->edited = true;
}


ll Message::getSentDate() {
	return this->sentDate;
}

Message::~Message() {
	//TODO: WRRITE EDITIONS
}