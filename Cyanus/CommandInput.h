#ifndef _COMMAND_INPUT_H_
#define _COMMAND_INPUT_H_
#include <queue>
#include <string>
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
};

#endif