#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "User.h"
#include "AVLTree.h"
#define ll long long

class Message {
private:
	User* sender;
	string message;
	AVLTree<string, ll> editions;
	ll sentDate;
	bool edited;

public:
	Message(User* sender, const string& message);
	Message(User* sender, const string& message, ll createdDate);

	string& getMessage();
	void change(const string& s);

	User* getSender();
	AVLTree<string, ll>& getEditions();
	ll getSentDate();


	~Message();
};

#endif