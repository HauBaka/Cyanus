#include "terminalUtils.h"
#include <iostream>
#include "UIManager.h"
#include <conio.h>
using namespace std;

int main() {
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
    return 0;
}
