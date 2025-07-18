#ifndef _CONVERSATION_PANEL_H_
#define _CONVERSATION_PANEL_H_
#include <string>
using namespace std;
class ConversationPanel {
private:
	string input;
public:
	void addInput(char c);
	string& getInput();
	void draw();
	void update();
	void execute();
};
#endif