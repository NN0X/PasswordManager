#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <set>
#include <vector>

namespace PM
{
        enum StorageMethod
        {
                PLAINTEXT,
                ENCRYPTED
        };

        enum EncryptionMethod
        {
                AES256,
                BRUTUS
        };

        enum QueryStatus
        {
                NONE,
                ONE,
                MULTIPLE
        };

        enum EventType
        {
                LOGIN_TIMEOUT_EVENT,
                PASSWORD_TIMEOUT_EVENT,
                TIMEOUT_EVENT,
                QUERY_EVENT
        };

        class Query
        {
        private:
                std::set<int> ids;
                std::set<std::string> names;
        public:
                QueryStatus status;

                Query() : status(NONE) {}

                void add(int id, const std::string &name);
                void print() const;
                std::vector<int> unpackID() const;
                std::vector<std::string> unpackName() const;
        };

        struct AccountData
        {
                std::string name;
                std::string login; // can be encrypted
                std::string password; // can be encrypted
        };

        class PasswordManager
        {
        private:
                std::string filename;
                std::vector<AccountData> accounts;
                std::string masterPassword;
                int encryptionType;
                int encryptionKeySize;
                int loginTimeout;
                int passwordTimeout;
                int totalTimeout;
                void (*loginTimeoutCallback)() = nullptr;
                void (*passwordTimeoutCallback)() = nullptr;
                void (*timeoutCallback)() = nullptr;
                void (*queryCallback)() = nullptr;
                void load();

        public:
                PasswordManager(const std::string &filename, int encryptionType, int encryptionKeySize, int loginTimeout, int passwordTimeout, int totalTimeout)
                        : filename(filename), encryptionType(encryptionType), encryptionKeySize(encryptionKeySize), loginTimeout(loginTimeout), passwordTimeout(passwordTimeout), totalTimeout(copyTimeout)
                {}

                void setMasterPassword(const std::string &password);
                void setCallback(int eventType, void (*callback)());
                void start();
                void stop();
                void queryByID(int id, Query &result);
                void queryByName(const std::string &name, Query &result);
        };
}

#endif // PASSWORDMANAGER_H
