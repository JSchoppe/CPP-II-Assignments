#include <vector>

#include "menu-item.hpp"
#include "currency-denomination.hpp"
#include "input-output.hpp"
#include "money-tools.hpp"
#include "command/command.hpp"
#include "command/root-command.hpp"
#include "command/list-menu-command.hpp"
#include "command/buy-command.hpp"

int main()
{
    // Initialize money tools to USD.
    money_tools::set_currency(CURRENCY::USD);
    // Set the starting wallet for the user.
    std::vector<CurrencyDenomination> user_wallet = money_tools::generate_wallet(
        std::vector<uint>{ 2000, 2000, 2000, 1000, 1000, 500, 500, 100, 100, 100 });
    money_tools::sort_wallet_in_place(user_wallet);

    // Generate the menu of items available to the player.
    std::vector<MenuItem> menu;
    menu.push_back(MenuItem("coffee", 215));
    menu.push_back(MenuItem("tea", 275));
    menu.push_back(MenuItem("sandwich", 350));
    menu.push_back(MenuItem("burger", 525));

    // Create the top level commands for the program.
    RootCommand help_command = RootCommand("help", "displays available commands");
    RootCommand exit_command = RootCommand("exit", "exits the program");
    ListMenuCommand list_command = ListMenuCommand(menu);
    BuyCommand buy_command = BuyCommand(menu, user_wallet);
    // Push the available commands onto an enumerable vector.
    std::vector<Command*> commands;
    commands.push_back(&help_command);
    commands.push_back(&exit_command);
    commands.push_back(&list_command);
    commands.push_back(&buy_command);

    // Top level command loop.
    while(true)
    {
        // Request a command from the user.
        std::string input = input_output::get_input();
        input_output::print_line();

        if(exit_command.TryParseStringArgs(input))
        {
            // Exit top level loop.
            break;
        }
        else if(help_command.TryParseStringArgs(input))
        {
            // Print available commands.
            input_output::print_command_tree(commands);
        }
        else
        {
            // Attempt to execute any commands.
            bool command_recognized = false;
            for(size_t i = 0; i < commands.size(); i++)
            {
                if(commands[i]->TryParseStringArgs(input))
                {
                    // Stop if/once a command is executed.
                    command_recognized = true;
                    break;
                }
            }
            if(!command_recognized)
            {
                std::vector<std::string> error = Command::GetInvalidCommandText();
                input_output::print_multiline(error);
            }
        }

        // Add spacing between commands.
        input_output::print_line();
    }
}