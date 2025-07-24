#ifndef _COMMAND_INPUT_H_
#define _COMMAND_INPUT_H_
#include <string>
#include <queue>
using namespace std;

class CommandInput {
private:
	string input;
	queue<string> logs; // Queue to store command history
public:
	void addInput(char c);
	void draw();
	string& getInput();
	void execute();
	void addToLogs(const string& s);
	void printLogs();
	vector<string> parseRawRequest();
	string toRequestString(vector<string>& args);
};



#endif