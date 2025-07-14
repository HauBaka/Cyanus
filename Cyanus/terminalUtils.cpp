#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
using namespace std;
void FixConsoleWindow() {
	/*Không cho thay đồi kích thước cửa sổ*/
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	/*Di chuyển cửa sổ đến góc trái trên và đặt kích thước là 1280x720 px*/
	MoveWindow(consoleWindow, 0, 0, 1280, 720, TRUE);//ngang 172, doc 42 ki tu
	/*Tắt thanh kéo*/
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);//TO DO: Not work
}
/*Bật/tắt con trỏ chuột nhấp nhấy*/
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
/*Đi đến tọa độ x,y trên cửa sổ*/
void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}