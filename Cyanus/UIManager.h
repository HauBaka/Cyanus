#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_
#include "FriendsPanel.h"
#include "UserPanel.h"
#include "ConversationPanel.h"
#include "CommandInput.h"
class UIManager {
private:
	FriendsPanel friendsPanel;
	UserPanel userPanel;
	ConversationPanel conversationPanel;
	CommandInput commandInput;
	void drawBorder();
public:
	enum InputType {
		COMMAND_INPUT,
		CONVERSATION_INPUT
	};

	void drawUI();
	void update();

	std::string& getConversationInput();
	std::string& getCommandInput();

	void setInput(InputType type, std::string& input, bool execute);
};
#endif