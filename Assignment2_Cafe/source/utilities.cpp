#include "utilities.hpp"

void utilities::string_to_lower_in_place(std::string& str)
{
    // Convert each character in the string to lowercase.
    const size_t size = str.size();
    for(size_t i = 0; i < size; i++)
    {
        str[i] = std::tolower(str[i]);
    }
}

std::vector<std::string> utilities::string_split(const std::string& str)
{
    std::vector<std::string> substrings;
    std::string current_chunk = "";

    const size_t size = str.size();
    for(size_t i = 0; i < size; i++)
    {
        // Concatenate characters until a delimiter is hit.
        if(str[i] != ' ')
        {
            current_chunk += str[i];
        }
        else if(current_chunk != "")
        {
            // If the concatenated string has length, push it onto the vector.
            substrings.push_back(current_chunk);
            current_chunk = "";
        }
    }
    // Check the final chunk at the end of the string.
    if(current_chunk != "")
    {
        substrings.push_back(current_chunk);
    }
    return substrings;
}