#ifndef _TERMINAL_UTILS_H_  
#define _TERMINAL_UTILS_H_  
#include <string>  

class TerminalUtils {  
private:  
    static void setCenteredTitle(const std::string& title);
    static void setConsoleTheme(int r, int g, int b);
    static void DisableQuickEdit();
public:  
    static void FixConsoleWindow();
    static void ShowConsoleCursor(bool show);  
    static void GotoXY(int x, int y);  
    static void SetUpWindow();  
};  

#endif