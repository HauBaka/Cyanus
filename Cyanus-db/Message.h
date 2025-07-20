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
	ll id;
	bool edited;

public:
	Message(User* sender, const string& message);
	Message(User* sender, const string& message, ll id);

	string& getMessage();
	void change(const string& s);


	User* getSender();
	AVLTree<string, ll>& getEditions();
	ll getID();


	~Message();
};

#endif