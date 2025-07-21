#include "Message.h"

Message::Message(const string& content, User* sender, long long ID)
	: content(content), sender(sender), id(ID) {
}
string Message::getContent() const {
	return content;
}
User* Message::getSender() const {
	return sender;
}
long long Message::getID() const {
	return id;
}
