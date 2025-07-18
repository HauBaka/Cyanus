#include "terminalUtils.h"
#include <iostream>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

using namespace std;
void TerminalUtils::DisableQuickEdit() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void TerminalUtils::FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();

    // Disable resizing and maximize
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);


    MoveWindow(consoleWindow, 0, 0, 1280, 700, TRUE);

	// Disable quick edit mode
	//DisableQuickEdit();
	//removeConsoleScrollbars();
}

void TerminalUtils::ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void TerminalUtils::GotoXY(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TerminalUtils::setCenteredTitle(const std::string& title) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - title.length()) / 2;
    if (padding < 0) padding = 0;

    string spacedTitle(padding, ' ');
    spacedTitle += title;

    SetConsoleTitleA(spacedTitle.c_str());
}

void TerminalUtils::setConsoleTheme(int r, int g, int b) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get buffer info
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hOut, &info);

    // Set background color index 0 to RGB
    info.ColorTable[0] = RGB(r, g, b);
    info.wAttributes = 0x0F; // white text, background 0

    // Force window and buffer size match (to avoid shrinking bug)
    SHORT width = info.srWindow.Right - info.srWindow.Left + 1;
    SHORT height = info.srWindow.Bottom - info.srWindow.Top + 1;
    info.dwSize = { width, height };

    SetConsoleScreenBufferInfoEx(hOut, &info);
    SetConsoleTextAttribute(hOut, 0x0F); // white text

    // Fill console with background
    DWORD written;
    COORD coord = { 0, 0 };
    DWORD size = width * height;

    FillConsoleOutputAttribute(hOut, 0x00, size, coord, &written);  // background index 0
    FillConsoleOutputCharacter(hOut, ' ', size, coord, &written);
    SetConsoleCursorPosition(hOut, coord);
}

void TerminalUtils::SetUpWindow() {
    FixConsoleWindow();
    //ShowConsoleCursor(false);
    setConsoleTheme(20, 29, 57); // oceanic blue
    setCenteredTitle("CYANUS");
    SetConsoleOutputCP(CP_UTF8); // Enable UTF-8 for symbols/emojis
}
