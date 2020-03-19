#include "command.hpp"
#include "../utilities.hpp"

std::vector<std::string> Command::GetInvalidCommandText()
{
    std::vector<std::string> info;
    info.push_back("command not recognized");
    info.push_back("use \"help\" to see available commands");
    return info;
}

bool Command::TryParseStringArgs(std::string input)
{
    // Convert to lowercase and split the tokens.
    utilities::string_to_lower_in_place(input);
    return TryParseArgs(utilities::string_split(input));
}

// Default behavior when overrides are not implemented.
std::vector<std::string> Command::GetHelp()
{
    std::vector<std::string> default_return;
    default_return.push_back("Help text has not been implemented for this command");
    return default_return;
}
bool Command::TryParseArgs(std::vector<std::string>)
{
    return false;
}