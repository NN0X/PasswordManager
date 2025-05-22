#include <iostream>

#include "config.h"

#include "clipboard.h"
#include "PasswordManager.h"

Clipboard clipboard = Clipboard();

void loginTimeoutCallback()
{
        std::cout << "Login timeout reached.\n";
        clipboard.clear();
}

void passwordTimeoutCallback()
{
        std::cout << "Password timeout reached.\n";
        clipboard.clear();
}

void timeoutCallback()
{
        std::cout << "Timeout reached.\n";
        clipboard.clear();
}

inline bool isNumber(const std::string &str)
{
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

int main()
{
        PM::PasswordManager pm("passwords.aes", PM::ENCRYPTED, PM::AES256, 20, 10, 60);
        pm.setCallback(PM::LOGIN_TIMEOUT_EVENT, loginTimeoutCallback);
        pm.setCallback(PM::PASSWORD_TIMEOUT_EVENT, passwordTimeoutCallback);
        pm.setCallback(PM::TIMEOUT_EVENT, timeoutCallback);

        std::cout << "Input master password: ";
        std::string masterPassword;
        std::cin >> masterPassword;
        pm.setMasterPassword(masterPassword);

        pm.start();
        std::string query;
        std::cout << "Enter query: ";
        std::cin >> query;

        PM::Query result;
        if (isNumber(query))
        {
                query--;
                pm.queryByID(std::stoi(query), result);
        }
        else
                pm.queryByName(query, result);

        int id = -1;
        switch (result.status)
        {
                case PM::Query::ONE:
                        id = result.unpackID()[0];
                        break;
                case PM::Query::MULTIPLE:
                        std::cout << "Multiple results found:\n";
                        result.print();
                        std::cout << "Select: ";
                        std::cin >> query;
                        if (isNumber(query))
                                id = std::stoi(query) - 1;
                        else
                        {
                                std::cerr << "Invalid input. Exiting.\n";
                                return 1;
                        }
                case PM::Query::NONE:
                        std::cerr << "No results found.\n";
                        return 1;
        }
        if (id == -1)
        {
                std::cerr << "Invalid ID. Exiting.\n";
                return 1;
        }
        clipboard.copy(pm.extractLogin(id));
        std::cout << "Login copied to clipboard.\n";
        clipboard.waitForPaste();
        clipboard.clear();
        clipboard.copy(pm.extractPassword(id));
        std::cout << "Password copied to clipboard.\n";
        clipboard.waitForPaste();
        clipboard.clear();
        pm.stop();
        std::cout << "Password manager stopped.\n";
}
