#ifndef APILINUXX11_H
#define APILINUXX11_H

#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <string>
#include <iostream>

enum Key
{
        NONE = 0,
        CTRL_V = 22,
};

inline int getKeyPressed()
{
        Display *display = XOpenDisplay(NULL);
        char keys[32];
        XQueryKeymap(display, keys);

        KeyCode key = XKeysymToKeycode(display, XK_V);
        bool isPressed = !!(keys[key / 8] & (0x1 << (key % 8)));
        XCloseDisplay(display);

        if (isPressed)
                return CTRL_V;

        return NONE;
}

inline void setClipboard(std::string text)
{
        std::string command = "echo '" + text + "' | xclip -selection clipboard";
        system(command.c_str());
}

inline void clear()
{
        std::cout << "\033[2J\033[1;1H";
}

inline void clearln(int line)
{
        std::cout << "\033[" << line << ";0H\033[K";
}

inline void msleep(int ms)
{
        usleep(ms * 1000);
}

inline std::string getExePath()
{
        char buffer[1000];
        readlink("/proc/self/exe", buffer, sizeof(buffer));
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, pos);
}

#endif
