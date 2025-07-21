#include "CommandProcessor.h"
#include "Cyanus.h"
string CommandProcessor::processCommand(vector<string>& args)
{
	if (args.empty() || args[0].empty() || stringToRequestType.find(args[0]) == stringToRequestType.end()) {
		return "Unknown command or invalid format.";
	}
	REQUEST_TYPE type = stringToRequestType.at(args[0]);
	string token, response;
	vector<string> parsedResponse;
	vector<string> tmp;
	switch (type) {
	case REGISTER:
		if (args.size() != 4) {
			return "Invalid command format. Use: /register <username> <displayName> <password>";
		}
		response = Cyanus::getInstance().
			getSocketManager().sendMessage(
				"REGISTER;" + args[1] + ";" + args[2] + ";" + args[3]);
		parsedResponse = parseRawResponse(response);

		if (parsedResponse.size() < 2) {
			return "Server response: " + response;
		}

		Cyanus::getInstance().getUserManager().setToken(parsedResponse[1]);
		if (parsedResponse[0] != "200") 
			return args[1];
		return "Registration failed: " + parsedResponse[1];
	case LOGIN:
		if (args.size() != 3) {
			return "Invalid command format. Use: /login <username> <password>";
		}
		
		response = Cyanus::getInstance().
			getSocketManager().sendMessage(
				"LOGIN;" + args[1] + ";" + args[2]);

		parsedResponse = parseRawResponse(response);
		if (parsedResponse.size() < 2) {
			return "Server response: " + response;
		}
		if (parsedResponse[0] != "200") {
			return "Login failed: " + parsedResponse[1];
		}
		Cyanus::getInstance().getUserManager().setToken(parsedResponse[1]);
		return "Login successful!";
	case LOGOUT:
		if (args.size() != 1) {
			return "Invalid command format. Use: /logout";
		}
		break;
	case DELETE_ACCOUNT:
		//not available now
		break;
	case CHANGE_PASSWORD:
		if (args.size() != 4) {
			return "Invalid command format. Use: /change_password <oldPassword> <newPassword>";
		}
		break;
	default:
		return "Unknown command or invalid format.";
	}
	return "...";
}

vector<string>& CommandProcessor::parseRawResponse(string& response)
{
	static vector<string> args;
	args.clear();
	if (response.empty()) {
		return args;
	}
	size_t prevPos = 0, curPos = response.find(';');
	while (curPos != string::npos) {
		args.push_back(response.substr(prevPos, curPos - prevPos));
		prevPos = curPos + 1;
		curPos = response.find(';', prevPos);
	}
	args.push_back(response.substr(prevPos)); // Add the last part after the last semicolon
	return args;
}
