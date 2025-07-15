#include "Conversation.h"
#include "Utils.h"
Conversation::Conversation(User* owner, string& name, ll& createdDate) : 
	owner(owner), name(name), createdDate(createdDate){}

void Conversation::sendMessage(Message* message) {
	addMessage(message);
	//send packet...
}
void Conversation::addMessage(Message* message) {
	auto node = messages.createNode(message, Utils::getCurrentTime());
	messages.add(node);
}
void Conversation::removeMessage(Message* message) {
	messages.remove(message->getSentDate());
	//send packet...
}

void Conversation::addNewMember(User* user) {
	addMember(user);
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
string& Conversation::getName() {
	return name;
}
void Conversation::writeString(ofstream& ofs, const string& s) {
	int len = s.size();
	ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
	ofs.write(s.c_str(), len); 
}

void Conversation::save(ofstream& ofs) {
	/*
	sender username
	conversation name
	createdDate

	member count
	member's username

	message count
	message's key
	message's content
	message's sender
	message's editions count
	edition's key
	edition's value
	*/
	writeString(ofs, owner->getUserName());
	writeString(ofs, name);
	ofs.write(reinterpret_cast<char*>(&createdDate), sizeof(ll));

	vector<pair<User*, string>> memberData = members.getAllData();
	int memberCount = memberData.size();
	ofs.write(reinterpret_cast<char*>(&memberCount), sizeof(int));

	for (int i = 0; i < memberCount; ++i) {
		writeString(ofs, memberData[i].second);
	}

	vector<pair<Message*, ll>> messageData = messages.getAllData();
	int messageCount = messageData.size();
	ofs.write(reinterpret_cast<char*>(&messageCount), sizeof(int));

	for (int i = 0; i < messageCount; ++i) {
		ll key = messageData[i].second;
		Message* message = messageData[i].first;

		ofs.write(reinterpret_cast<char*>(&key), sizeof(ll));
		writeString(ofs, message->getMessage());
		writeString(ofs, message->getSender()->getUserName());
		
		
		vector<pair<string, ll>> edits = message->getEditions().getAllData();
		int editCount = edits.size();
		ofs.write(reinterpret_cast<char*>(&editCount), sizeof(int));

		for (int j = 0; j < editCount; ++j) {
			ofs.write(reinterpret_cast<char*>(&edits[j].second), sizeof(ll));
			writeString(ofs, edits[j].first);
		}
	}
}

Conversation::~Conversation() {
	//Todo: save to file before remove trees.
}