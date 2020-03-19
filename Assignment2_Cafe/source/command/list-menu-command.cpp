#include <iostream>

#include "list-menu-command.hpp"
#include "../money-tools.hpp"

ListMenuCommand::ListMenuCommand(std::vector<MenuItem> menu_items)
{
    menu = menu_items;
}

std::vector<std::string> ListMenuCommand::GetHelp()
{
    std::vector<std::string> info;
    info.push_back("list: shows the available menu items and their prices");
    return info;
}

bool ListMenuCommand::TryParseArgs(std::vector<std::string> args)
{
    // Is the command signature a match?
    if(args.size() == 1 && args[0] == "list")
    {
        std::vector<std::string> item_price_strings;
        std::vector<uint> line_character_counts;
        uint max_character_count = 0;
        for(size_t i = 0; i < menu.size(); i++)
        {
            item_price_strings.push_back(money_tools::cents_to_string(menu[i].price));
            line_character_counts.push_back(menu[i].name.size() + item_price_strings[i].size());

            if(line_character_counts[i] > max_character_count)
            {
                max_character_count = line_character_counts[i];
            }
        }
        max_character_count += 3;

        for(size_t i = 0; i < menu.size(); i++)
        {
            std::cout << menu[i].name;

            for(uint j = 0; j < max_character_count - line_character_counts[i]; j++)
            {
                std::cout << ".";
            }
            std::cout << item_price_strings[i];

            std::cout << std::endl;
        }

        // Return true if the command was executed.
        return true;
    }
    return false;
}