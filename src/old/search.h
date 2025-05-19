#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

std::vector<int> genIndices(const std::vector<std::string>& names);
std::vector<int> search(std::string searchWord, const std::vector<std::string>& names);

#endif
