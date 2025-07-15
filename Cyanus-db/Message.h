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
	bool Editied;
public:
	void change(const string& s);
};
#endif