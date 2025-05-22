#ifndef CLIPBOARD_H
#define CLIPBOARD_H


#ifdef X11
void attachX11Clipboard();
#define attachClipboard attachX11Clipboard
#elif defined(WIN32)
void attachWin32Clipboard();
#define attachClipboard attachWin32Clipboard
#else
#pragma error "Unsupported platform"
#endif

class Clipboard
{
private:
        std::string *content;

public:
        Clipboard();
        ~Clipboard();

        void copy(const std::string &content);
        void clear();
        void waitForPaste();
}

#endif // CLIPBOARD_H
