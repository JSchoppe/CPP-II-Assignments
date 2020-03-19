#include "root-command.hpp"

RootCommand::RootCommand(std::string command_word, std::string help_description)
{
    command = command_word;
    help_text = help_description;
}

std::vector<std::string> RootCommand::GetHelp()
{
    std::vector<std::string> help;
    help.push_back(command + ": " + help_text);
    return help;
}

bool RootCommand::TryParseArgs(std::vector<std::string> args)
{
    // Return true if the command signature is matched.
    if(args.size() == 1 && args[0] == command)
    {
        return true;
    }
    return false;
}
