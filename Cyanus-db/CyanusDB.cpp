#include "CyanusDB.h"
#include "Utils.h"
UserManager& CyanusDB::userManager() {
	return userMng;
}

ConversationManager& CyanusDB::conversationManager() {
	return conversationMng;
}

void CyanusDB::save() {
	saveUsers();
	saveConversations();
}

void CyanusDB::load() {
	readUsers();
	readConversations();
}

CyanusDB::~CyanusDB()
{
	save();
}

void CyanusDB::saveUsers() {
	ofstream ofs("users.bin", ios::binary);
	vector<pair<User*, string>> users = userMng.getUserDatabase().getAllData();
	int userCount = users.size();
	ofs.write(reinterpret_cast<char*>(&userCount), sizeof(userCount));
	
	for (pair<User*, string>& P : users) {
		
		P.first->save(ofs);

		AVLTree<Conversation*, ll>& conversationsTree = userMng.getConversationDatabase().findNodeByKey(P.second)->data;
		vector<pair<Conversation*, ll>> conversations = conversationsTree.getAllData();
		
		int conversationCount = conversations.size();
		ofs.write(reinterpret_cast<char*>(&conversationCount), sizeof(int));

		for (pair<Conversation*, ll>& C : conversations) {
			ofs.write(reinterpret_cast<char*>(&C.second), sizeof(ll));
		}
	}
	ofs.close();
}


void CyanusDB::saveConversations() {
	ofstream ofs("conversations.bin", ios::binary);
	vector<pair<Conversation*, ll>> conversations = conversationMng.getConversationDatabase().getAllData();
	int conversationCount = conversations.size();
	ofs.write(reinterpret_cast<char*>(&conversationCount), sizeof(conversationCount));

	for (pair<Conversation*, ll> P : conversations) {
		P.first->save(ofs);
	}
	ofs.close();
}

void CyanusDB::readUsers() {
	ifstream ifs("users.bin", ios::binary | ios::ate);
	if (ifs.tellg() == 0) {
		cout << "[CyanusDB] No users found in file.\n";
		return;
	}
	ifs.seekg(0);


	int userCount;
	ifs.read(reinterpret_cast<char*>(&userCount), sizeof(int));

	for (int i = 0; i < userCount; ++i) {
		//Read user data
		string userName, displayName, hashedPassword, token;
		ll firstLogin, lastLogin;

		Utils::readString(ifs, userName);
		Utils::readString(ifs, displayName);
		Utils::readString(ifs, hashedPassword);
		Utils::readString(ifs, token);
		
		ifs.read(reinterpret_cast<char*>(&firstLogin), sizeof(ll));
		ifs.read(reinterpret_cast<char*>(&lastLogin), sizeof(ll));

		User* user = new User(userName, displayName, hashedPassword, firstLogin, lastLogin, token);

		userMng.addUser(user);

	}
	cout << "[CyanusDB] Loaded " << userCount << " users from file.\n";
	ifs.close();
}

void CyanusDB::readConversations() {
	ifstream ifs("conversations.bin", ios::binary | ios::ate);
	if (ifs.tellg() == 0) {
		cout << "[CyanusDB] No conversations found in file.\n";
		return;
	}
	ifs.seekg(0);


	int conversationCount;
	ifs.read(reinterpret_cast<char*>(&conversationCount), sizeof(int));

	for (int i = 0; i < conversationCount; ++i) {
		string ownerName, name;
		ll conversationID;
		int memberCount, messageCount;

		Utils::readString(ifs, ownerName);
		Utils::readString(ifs, name);
		ifs.read(reinterpret_cast<char*>(&conversationID), sizeof(ll));

		User* owner = userMng.getUser(ownerName);
		Conversation* conversation = new Conversation(owner, name, conversationID);

		//Read members
		ifs.read(reinterpret_cast<char*>(&memberCount), sizeof(int));

		for (int j = 0; j < memberCount; ++j) {
			string memberName;

			Utils::readString(ifs, memberName);
			User* member = userMng.getUser(memberName);

			if (!member) {
				cerr << "[CyanusDB] User " << memberName << " not found in user database.\n";
				continue; // Skip if member not found
			}

			//Add member to conversation
			conversation->addMember(member);

			//Add conversation to member's conversation tree
			AVLTree<Conversation*, ll>& conversationTree = userMng.getConversationDatabase().findNodeByKey(memberName)->data;
			
			conversationTree.add(
				conversationTree.createNode(conversation, conversation->getID())
			);

		}

		//Read messages
		ifs.read(reinterpret_cast<char*>(&messageCount), sizeof(int));

		for (int j = 0; j < messageCount; ++j) {
			ll msgID;
			string msgValue, msgSenderName;
			int editCount;

			ifs.read(reinterpret_cast<char*>(&msgID), sizeof(ll));
			Utils::readString(ifs, msgValue);
			Utils::readString(ifs, msgSenderName);

			Message* message = new Message(userMng.getUser(msgSenderName), msgValue, msgID);

			//Read edits
			ifs.read(reinterpret_cast<char*>(&editCount), sizeof(int));
			for (int k = 0; k < editCount; ++k) {
				ll editID;
				string editValue;

				ifs.read(reinterpret_cast<char*>(&editID), sizeof(ll));
				Utils::readString(ifs, editValue);

				message->getEditions().add(
					message->getEditions().createNode(editValue, editID)
				);
		    }
			conversation->addMessage(message);
		}
		//Add conversation to conversation manager
		conversationMng.addConversation(conversation);
	}
	cout << "[CyanusDB] Loaded " << conversationCount << " conversations from file.\n";
}