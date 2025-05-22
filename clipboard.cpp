#include "clipboard.h"

#ifdef WIN32
void attachWin32Clipboard()
{
}
#endif // WIN32

#ifdef X11
void attachX11Clipboard()
{
}
#endif // X11

Clipboard::Clipboard()
{
        content = new std::string();
        attachClipboard();
}
