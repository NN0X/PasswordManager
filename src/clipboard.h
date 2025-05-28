#ifndef CLIPBOARD_H

#ifdef X11
#include "linux/x11api.h"
#elif defined(WAYLAND)
#include "linux/waylandapi.h"
#elif defined(WIN32)
#include "windows/winapi.h"
#elif defined(MACOS)
#include "macos/macosapi.h"
#else
#pragma error "No clipboard support implemented for this platform."
#endif

class Clipboard
{
private:
        std::string mContent;
        void copyCallback();
        void pasteCallback();

public:
        Clipboard();
        ~Clipboard();

        void setContent(const std::string &text);
        void clearContent();

        void setCopyCallback(void (*callback)());
        void setPasteCallback(void (*callback)());
};

#endif // CLIPBOARD_H
