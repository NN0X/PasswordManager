#include "loader.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "api.h"

AccountsData loadNotEncrypted(std::string path)
{
        path = getExePath() + "/" + path;
        std::ifstream file(path);

        AccountsData data;

        if (file.is_open())
        {
                std::string line;
                while (std::getline(file, line))
                {
                        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

                        std::size_t pos = line.find(':');
                        std::string name = line.substr(0, pos);
                        line.erase(0, pos + 1);

                        pos = line.find(':');
                        std::string login = line.substr(0, pos);
                        line.erase(0, pos + 1);

                        std::string password = line;

                        data.names.push_back(name);
                        data.logins.push_back(login);
                        data.passwords.push_back(password);
                }
        }
        else
        {
                std::cerr << "Error: Could not open file.\n";
        }

        file.close();

        return data;
}

