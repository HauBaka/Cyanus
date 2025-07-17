#ifndef _CONVERSATION_PANEL_H_
#define _CONVERSATION_PANEL_H_
#include <string>
using namespace std;
class ConversationPanel {
private:
	string input;
public:
	void setInput(string& newInput);
	string& getInput();
	void draw();
	void update();
	void execute();
};
#endif