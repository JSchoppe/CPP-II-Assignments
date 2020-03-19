#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command
{
    public:
        bool TryParseStringArgs(std::string);
        virtual std::vector<std::string> GetHelp();
        static std::vector<std::string> GetInvalidCommandText();
    protected:
        virtual bool TryParseArgs(std::vector<std::string>);
};

#endif