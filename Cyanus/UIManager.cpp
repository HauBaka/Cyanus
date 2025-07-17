#include "UIManager.h"
#include "terminalUtils.h"
#include "DrawingUtils.h"
#include <vector>
#include <string>
#include <iostream>

const std::vector<std::string> borders = {
u8"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃         ⧉ CONVERSATIONS        ┃                                   🌀 𝐂𝐘𝐀𝐍𝐔𝐒 - 𝐂𝐇𝐀𝐓 𝐑𝐎𝐎𝐌                                       ┃              📄 INFORMATIONS",
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
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┃                                ┃                                                                                               ┃                                          ┃",
u8"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
u8"┃      LOGS:                                                                                                                                                                ┃",
u8"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
};
void UIManager::drawBorder()
{
	
	for (int i = 0; i < borders.size(); i++)
	{
		DrawingUtils::draw(1, i+1, borders[i], DrawingUtils::DEFAULT_TEXT_COLOR);
	}
	DrawingUtils::draw(173, 3, u8"┃", DrawingUtils::DEFAULT_TEXT_COLOR);
}

void UIManager::drawUI()
{
	drawBorder();
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

void UIManager::setInput(UIManager::InputType type, std::string& input, bool execute)
{
	switch (type) {
	case COMMAND_INPUT:
		commandInput.setInput(input);
		if (execute) {
			commandInput.execute();
		}
		break;
	case CONVERSATION_INPUT:
		conversationPanel.setInput(input);
		if (execute) {
			conversationPanel.execute();
		}
		break;
	}
}