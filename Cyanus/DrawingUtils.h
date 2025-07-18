#ifndef _DRAWING_UTILS_H_  
#define _DRAWING_UTILS_H_  
#include <string>  

class DrawingUtils {  

public:  
    struct RGB {  
        int r, g, b;  
        RGB(int red, int green, int blue) : r(red), g(green), b(blue) {}  
    };  

    static RGB 
        DEFAULT_TEXT_COLOR,
        DEFAULT_TIP_COLOR,
		DEFAULT_BG_COLOR,
        WHITE;

    static void draw(int x, int y, std::string& text, RGB& textColor);  
    static void draw(int x, int y, const std::string& text, RGB& textColor);  
    static void draw(int x, int y, std::string& text, RGB& textColor, RGB& bgColor);  
    static void draw(int x, int y, const std::string& text, RGB& textColor, RGB& bgColor);  



};  



#endif