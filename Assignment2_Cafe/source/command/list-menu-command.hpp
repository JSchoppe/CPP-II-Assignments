#ifndef LIST_MENU_COMMAND_H
#define LIST_MENU_COMMAND_H

#include "command.hpp"
#include "../menu-item.hpp"

class ListMenuCommand final : public Command
{
    public:
        ListMenuCommand(std::vector<MenuItem>);
        std::vector<std::string> GetHelp() override;
    private:
        bool TryParseArgs(std::vector<std::string>) override;
        std::vector<MenuItem> menu;
};

#endif