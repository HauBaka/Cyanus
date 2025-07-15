#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "User.h"
#include "AVLTree.h"
#define ll long long

class Message {
private:
	const User* sender;
	string message;
	AVLTree<string, ll> editions;
	ll sentDate;
	bool edited;

public:
	Message(const User& sender, const string& message);
	void change(const string& s);
	ll getSentDate();
	~Message();
};

#endif