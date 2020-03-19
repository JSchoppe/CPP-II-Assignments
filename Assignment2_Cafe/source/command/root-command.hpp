#ifndef ROOT_COMMAND_H
#define ROOT_COMMAND_H

#include <string>
#include <vector>

#include "command.hpp"

// The root command only checks for the command name and returns true.
// Use this for simple commands that will trigger actions on a higher scope.
class RootCommand final : public Command
{
    public:
        RootCommand(std::string, std::string);
        std::vector<std::string> GetHelp() override;
    private:
        bool TryParseArgs(std::vector<std::string>) override;
        std::string command;
        std::string help_text;
};

#endif