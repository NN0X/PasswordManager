#include "PasswordManager.h"

void PM::Query::add(int id, const std::string &name)
{
        if (ids.find(id) != ids.end())
                return;
        if (names.find(name) != names.end())
                return;

        ids.insert(id);
        names.insert(name);
        if (status == NONE)
                status = ONE;
        else if (status == ONE)
                status = MULTIPLE;
}

std::vector<int> PM::Query::unpackID() const
{
        std::vector<int> result;
        for (const auto &id : ids)
                result.push_back(id);
        return result;
}

std::vector<std::string> PM::Query::unpackName() const
{
        std::vector<std::string> result;
        for (const auto &name : names)
                result.push_back(name);
        return result;
}

void PM::Query::print() const
{
        std::vector<int> ids = unpackID();
        std::vector<std::string> names = unpackName();
        for (size_t i = 0; i < ids.size(); ++i)
        {
                std::cout << ids[i] + 1 << ": " << names[i] << "\n";
        }
}
