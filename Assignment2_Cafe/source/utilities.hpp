#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

struct utilities final
{
    static void string_to_lower_in_place(std::string&);
    static std::vector<std::string> string_split(const std::string&);
};

#endif