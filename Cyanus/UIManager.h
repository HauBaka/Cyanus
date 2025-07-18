#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_
#include "FriendsPanel.h"
#include "UserPanel.h"
#include "ConversationPanel.h"
#include "CommandInput.h"

enum InputType {
	COMMAND_INPUT,
	CONVERSATION_INPUT
};

class UIManager {
private:
	FriendsPanel friendsPanel;
	UserPanel userPanel;
	ConversationPanel conversationPanel;
	CommandInput commandInput;
	void init();
	InputType currentInputType;
public:
	UIManager();

	void drawUI();
	void update();

	std::string& getConversationInput();
	std::string& getCommandInput();

	void switchInput();

	void executeInput();

	void addToInput(char c);
};
#endif