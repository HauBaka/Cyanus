#ifndef _COMMAND_INPUT_H_
#define _COMMAND_INPUT_H_

#include <string>
using namespace std;

class CommandInput {
private:
	string input;
public:
	void setInput(string& newInput);
	string& getInput();
	void execute();
};

#endif