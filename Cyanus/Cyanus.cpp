#include "Cyanus.h"
#include "terminalUtils.h"
#include <iostream>
#include "UIManager.h"
#include <conio.h>
using namespace std;


int main() {
	Cyanus::getInstance().run();
}

void Cyanus::run() {
    if (!getSocketManager().connectToServer("127.0.0.1", 6969)) {
        cerr << "Failed to connect to server." << endl;
        return;
    }

    TerminalUtils::SetUpWindow();



    UIManager uiManager;
    uiManager.drawUI();

    while (true) {
        if (_kbhit()) {
            char input = _getch();

            switch (input) {
            case 9:
                uiManager.switchInput();
                break;
            default:
                uiManager.addToInput(input);

            }
        }
    }
}

SocketManager& Cyanus::getSocketManager() {
	return socketManager;
}

UserManager& Cyanus::getUserManager()
{
    return UserManager::getInstance();
}

