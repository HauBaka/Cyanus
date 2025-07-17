#include "CommandInput.h"

void CommandInput::setInput(string& newInput) {
	input = newInput;
}

string& CommandInput::getInput() {
	return input;
}

void CommandInput::execute() {
	// Execute the command based on the input
}