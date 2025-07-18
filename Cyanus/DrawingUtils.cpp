#include "DrawingUtils.h"
#include "terminalUtils.h"
#include <iostream>
using namespace std;
DrawingUtils::RGB DrawingUtils::DEFAULT_TEXT_COLOR(65, 172, 239);
DrawingUtils::RGB DrawingUtils::DEFAULT_TIP_COLOR(117, 143, 166);
DrawingUtils::RGB DrawingUtils::DEFAULT_BG_COLOR(20, 29, 57);
DrawingUtils::RGB DrawingUtils::WHITE(234, 248, 252);
void DrawingUtils::draw(int x, int y, std::string& text, RGB& textColor, RGB& bgColor)
{
	TerminalUtils::GotoXY(x, y);
    cout << "\x1b[38;2;" << textColor.r << ";" << textColor.g << ";" << textColor.b << "m";//text color
    cout << "\x1b[48;2;" << bgColor.r << ";" << bgColor.g << ";" << bgColor.b << "m";//bg color
    cout << text;
}
void DrawingUtils::draw(int x, int y,const std::string& text, RGB& textColor, RGB& bgColor)
{
    TerminalUtils::GotoXY(x, y);
    cout << "\x1b[38;2;" << textColor.r << ";" << textColor.g << ";" << textColor.b << "m";//text color
    cout << "\x1b[48;2;" << bgColor.r << ";" << bgColor.g << ";" << bgColor.b << "m";//bg color
    cout << text;
}



void DrawingUtils::draw(int x, int y, std::string& text, RGB& textColor)
{
    TerminalUtils::GotoXY(x, y);
    cout << "\x1b[38;2;" << textColor.r << ";" << textColor.g << ";" << textColor.b << "m";//text color
	cout << text;
}

void DrawingUtils::draw(int x, int y, const std::string& text, RGB& textColor)
{
    TerminalUtils::GotoXY(x, y);
    cout << "\x1b[38;2;" << textColor.r << ";" << textColor.g << ";" << textColor.b << "m";//text color
    cout << text;
}
