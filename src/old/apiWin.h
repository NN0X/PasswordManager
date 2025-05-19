#ifndef APIWIN_H
#define APIWIN_H

#include <windows.h>
#include <string>
#include <iostream>

enum Key
{
        NONE = 0,
        CTRL_V = 22,
};

inline int getKeyPressed()
{
        if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('V'))
                return CTRL_V;
        return NONE;
}

inline void setClipboard()
{
        std::cerr << "Error: setClipboard() is not supported on Windows.\n";
}

inline void clear()
{
        system("cls");
}

inline void msleep(int ms)
{
        Sleep(ms);
}

inline std::string getExePath()
{
        char buffer[1000];
        GetModuleFileName(NULL, buffer, 1000);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, pos);
}

#endif
