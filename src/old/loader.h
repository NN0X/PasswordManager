#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>

struct AccountsData
{
        std::vector<std::string> names;
        std::vector<std::string> logins;
        std::vector<std::string> passwords;
};

AccountsData loadNotEncrypted(std::string path);

#endif
