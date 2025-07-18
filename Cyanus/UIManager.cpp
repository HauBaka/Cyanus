#include "UIManager.h"
#include "terminalUtils.h"
#include "DrawingUtils.h"
#include <vector>
#include <string>
#include <iostream>

const std::vector<std::string> borders = {
u8"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
u8"┃                                                                                                                                                                           ┃",
u8"┃                                                                                                                                                                           ┃",
u8"┃                                                                                                                                                                           ┃",
u8"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
};

UIManager::UIManager()
{
	currentInputType = CONVERSATION_INPUT; // Default input type
}

void UIManager::init()
{
	
	// Draw the borders
	for (int i = 0; i < borders.size(); i++)
	{
		DrawingUtils::draw(1, i+2, borders[i], DrawingUtils::DEFAULT_TEXT_COLOR);
	}

	// Add default text
	DrawingUtils::draw(10, 4, u8"⧉ CONVERSATIONS", DrawingUtils::DEFAULT_TEXT_COLOR);
	DrawingUtils::draw(83, 1, u8"🌀 𝐂𝐘𝐀𝐍𝐔𝐒", DrawingUtils::DEFAULT_TEXT_COLOR);
	DrawingUtils::draw(78, 4, u8"𝐂𝐇𝐀𝐓 𝐑𝐎𝐎𝐌", DrawingUtils::DEFAULT_TEXT_COLOR);
	DrawingUtils::draw(144, 4, u8"📄 INFORMATIONS", DrawingUtils::DEFAULT_TEXT_COLOR);


	DrawingUtils::draw(14, 8, u8"NO DATA!", DrawingUtils::DEFAULT_TIP_COLOR);

	DrawingUtils::draw(68, 33, u8"Select a conversation first!", DrawingUtils::DEFAULT_TIP_COLOR);

	DrawingUtils::draw(133, 33, u8">>", DrawingUtils::WHITE);
	DrawingUtils::draw(136, 33, u8"Enter command here...", DrawingUtils::DEFAULT_TIP_COLOR);

	//Footer
	DrawingUtils::draw(6, 37, u8"User Name:", DrawingUtils::WHITE);
	DrawingUtils::draw(17, 37, u8"NO DATA!", DrawingUtils::DEFAULT_TIP_COLOR);

	DrawingUtils::draw(38, 37, u8"Name:", DrawingUtils::WHITE);
	DrawingUtils::draw(44, 37, u8"NO DATA!", DrawingUtils::DEFAULT_TIP_COLOR);

	DrawingUtils::draw(81, 37, u8"Status:", DrawingUtils::WHITE);
	DrawingUtils::draw(89, 37, u8"⚫", DrawingUtils::DEFAULT_TIP_COLOR);

	switchInput(); // Initialize the input panel
}



void UIManager::drawUI()
{
	init();
	//friendsPanel.draw();
	//userPanel.draw();
	//conversationPanel.draw();
}


std::string& UIManager::getConversationInput()
{
	return conversationPanel.getInput();
}

std::string& UIManager::getCommandInput()
{
	return commandInput.getInput();
}

void UIManager::switchInput() {
	if (currentInputType == COMMAND_INPUT) {
		currentInputType = CONVERSATION_INPUT;
		conversationPanel.draw(); 
	} else {
		currentInputType = COMMAND_INPUT;
		commandInput.draw(); 
	}
}
void UIManager::executeInput() {
	switch (currentInputType) {
	case COMMAND_INPUT:
		commandInput.execute();
		break;
	case CONVERSATION_INPUT:
		conversationPanel.execute();
		break;
	}
}
void UIManager::addToInput(char c)
{
	switch (currentInputType) {
	case COMMAND_INPUT:
		commandInput.addInput(c);
		break;
	case CONVERSATION_INPUT:
		conversationPanel.addInput(c);
		break;
	}
}