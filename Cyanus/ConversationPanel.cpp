#include "ConversationPanel.h"


void ConversationPanel::draw() {
	// Drawing logic for the conversation panel
	// This could include drawing the conversation history, input box, etc.
}
void ConversationPanel::update() {
	// Update logic for the conversation panel
	// This could include refreshing the conversation history, handling input, etc.
}
void ConversationPanel::setInput(string& newInput) {
	input = newInput;
}
string& ConversationPanel::getInput() {
	return input;
}
void ConversationPanel::execute() {
	// Execute the command based on the input
	// This could include sending a message, processing commands, etc.
}