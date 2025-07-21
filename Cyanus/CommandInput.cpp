#include "CommandInput.h"
#include "DrawingUtils.h"
#include "terminalUtils.h"
#include "Utils.h"
#include "CommandProcessor.h"
#include "Cyanus.h"
void CommandInput::addInput(char c) {
	if ((c == 8 || c == 127)) {
		if (!input.empty()) input.pop_back();
	}
	else if (c == 13) {
		execute();
		addToLogs(input);	
		input= "";
	}
	else {   
		if (input.size() >= 128) return;
		input += c;
	}
	draw();
}

string& CommandInput::getInput() {
	return input;
}

void CommandInput::execute() {
	if (input.empty()) return;

	vector<string> args = parseRawRequest();


	string response = CommandProcessor::getInstance().processCommand(args);

	addToLogs(input);
	addToLogs(response);
	printLogs();

}


void CommandInput::addToLogs(const string& s)
{
	string log = "[" + Utils::getCurrentTimeString("%H:%M:%S") + "] " + s;

	//Divine log into parts which are not longer than 40 characters
	int i = 0;
	while (i < log.size()) {
		string part = log.substr(i, 40);
		logs.push(part);
		i += 40;
	}
	while (logs.size() > 9) {
		logs.pop();
	}
}

void CommandInput::printLogs() {


	//Print the log to the console
	int size = logs.size();
	for (int i = 0; i < size; i++) {
		string& s = logs.front();

		DrawingUtils::draw(132, 23 + i, "                                    ", DrawingUtils::WHITE);
		DrawingUtils::draw(132, 23 + i, s, DrawingUtils::DEFAULT_TIP_COLOR);

		logs.push(s); logs.pop();
	}
}

vector<string>& CommandInput::parseRawRequest()
{
	vector<string> args;
	if (input.empty() || input[0] != '/') return args;

	string currentArg;

	for (int i= 1; i < input.size(); i++) { // Start from 1 to skip the '/'
		if (input[i] == ' ') {
			if (!currentArg.empty()) {
				args.push_back(currentArg);
				currentArg.clear();
			}
		}
		else {
			currentArg += input[i];
		}
	}

	if (!currentArg.empty()) {
		args.push_back(currentArg);
	}
	return args;
}

string CommandInput::toRequestString(vector<string>& args)
{
	string request;
	for (char &c : args[0]) {
		c = toupper(c); // Convert the command to uppercase
	}
	for (const string& arg : args) {
		if (!request.empty()) {
			request += ";";
		}
		request += arg;
	}
	return request;
}

void CommandInput::draw() {

	DrawingUtils::draw(133, 33, ">>                                      ", DrawingUtils::WHITE);

	int size = input.size();

	if (size <= 36) {
		DrawingUtils::draw(136, 33, input, DrawingUtils::WHITE);
		TerminalUtils::GotoXY(136 + size, 33);
	}
	else DrawingUtils::draw(136, 33, input.substr(size - 36), DrawingUtils::WHITE);
	
}
