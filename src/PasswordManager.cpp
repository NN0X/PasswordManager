#include "PasswordManager.h"

void PM::PasswordManager::load()
{

}

void PM::PasswordManager::setCallback(EventType event, void (*callback)())
{
        switch (event)
        {
                case LOGIN_TIMEOUT_EVENT:
                        loginTimeoutCallback = callback;
                        break;
                case PASSWORD_TIMEOUT_EVENT:
                        passwordTimeoutCallback = callback;
                        break;
                case TIMEOUT_EVENT:
                        timeoutCallback = callback;
                        break;
                default:
                        std::cerr << "Error: Invalid event type.\n";
        }
}

void PM::PasswordManager::start()
{
}

void PM::PasswordManager::stop()
{
}

void PM::PasswordManager::setMasterPassword(const std::string &password)
{
        masterPassword = password;
}

void PM::PasswordManager::queryByID(int id, Query &result)
{
        if (id < 0 || id >= accounts.size())
        {
                std::cerr << "Error: Invalid ID.\n";
                return;
        }
        result.add(id, accounts[id].name);
}

void PM::PasswordManager::queryByName(const std::string &name, Query &result)
{
        // TODO: Implement query by name so it doesn't require a specific match
}
