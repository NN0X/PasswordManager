#include "search.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> genIndices(const std::vector<std::string>& names)
{
        std::vector<int> indices;
        for (int i = 0; i < names.size(); i++)
        {
                indices.push_back(i);
        }

        return indices;
}

void printSearch(const std::vector<int> &foundIndices, const std::vector<std::string> &names)
{
        if (foundIndices.size() == 0)
        {
                std::cout << "No results found." << std::endl;
        }
        else
        {
                for (int i : foundIndices)
                {
                        std::cout << i + 1 << ". " <<names[i] << "\n";
                }
        }
        std::cin.get();
        std::cin.get();
}

std::vector<int> search(std::string query, const std::vector<std::string>& names)
{
        std::vector<int> indices = genIndices(names);
        if (query == "")
                return indices;

        std::vector<int> results;
        std::transform(query.begin(), query.end(), query.begin(), ::tolower);
        for (int i = 0; i < names.size(); i++)
        {
                std::string name = names[i];
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                if (name.find(query) != std::string::npos)
                {
                        results.push_back(i);
                }
        }

        return results;
}
