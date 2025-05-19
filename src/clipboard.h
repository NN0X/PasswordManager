#ifndef CLIPBOARD_H
#define CLIPBOARD_H

class Clipboard
{
public:
        Clipboard() = default;

        void copy(const std::string &text);
        void waitForPaste();
}

#endif // CLIPBOARD_H
