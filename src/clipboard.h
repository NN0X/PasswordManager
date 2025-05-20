#ifndef CLIPBOARD_H
#define CLIPBOARD_H

class Clipboard
{
private:
        std::string &content;

public:
        Clipboard() = default;

        void copy(const std::string &content);
        void copyManaged(std::string &content); // INFO: this will copy the text but the text can be modified after copying
        void waitForPaste();
}

#endif // CLIPBOARD_H
