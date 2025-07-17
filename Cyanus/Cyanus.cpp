#include "terminalUtils.h"
#include <iostream>
#include "UIManager.h"
#include <conio.h>
using namespace std;

int main() {
    TerminalUtils::SetUpWindow();
    //out << u8"🌀 â ă đ ê ô ơ \n";
   /* for (int i = 0; i < 40; i++) {
        cout << i+1 << "\n";
	}*/

	UIManager uiManager;
    uiManager.drawUI();
    while (true) {
        if (_kbhit()) {
            char input = _getch();
			cout << "You pressed: " << input << endl;
        }

    }
    return 0;
}
