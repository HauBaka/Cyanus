#include "ConversationPanel.h"


void ConversationPanel::draw() {
	
}
void ConversationPanel::update() {
	// Update logic for the conversation panel
	// This could include refreshing the conversation history, handling input, etc.
}
void ConversationPanel::addInput(char c) {
	if (c == 127) {
		if (!input.empty()) {
			input.pop_back();
		}
	} else if (c == 13) { 
		execute(); 
		input.clear(); 
	}
	else {
		input += c;
	}
	draw();
}
string& ConversationPanel::getInput() {
	return input;
}
void ConversationPanel::execute() {
	// Execute the command based on the input
	// This could include sending a message, processing commands, etc.
}