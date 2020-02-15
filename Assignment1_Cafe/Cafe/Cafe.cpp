// Cafe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>

struct MenuItem
{
    std::string name;
    double price;

    MenuItem(std::string _name, double _price)
    {
        name = _name;
        price = _price;
    }
    MenuItem()
    {
        name = "null";
        price = 0;
    }
};

int main()
{
    // Define recognized input patterns.
    std::regex helpCommand("^(help|HELP)$");
    std::regex listCommand("^(list|LIST)$");
    std::regex exitCommand("^(exit|EXIT)$");
    std::regex buyCommand("^([A-Za-z]+[[:space:]][0-9]+[[:space:]]*)+$");
    std::regex buyIndividual("[A-Za-z]+[[:space:]][0-9]+[[:space:]]*");
    // Define the available menu items.
    MenuItem items[4] = {
        MenuItem("Coffee", 2.15),
        MenuItem("Tea", 2.75),
        MenuItem("Sandwich", 3.50),
        MenuItem("Burger", 5.25)
    };

    bool inProgram = true;
    while (inProgram)
    {
        // Prompt user.
        std::cout << "Enter a command. Use 'help' to see commands." << std::endl;
        std::string userInput;
        std::getline(std::cin, userInput);

        // Check user input against commands.
        if (std::regex_match(userInput, helpCommand))
        {
            std::cout << "Available commands:" << std::endl;
            std::cout << "list: shows available menu options" << std::endl;
            std::cout << "{MenuItem} {Quantity}: calculates total cost for an order" << std::endl;
            std::cout << "exit: ends the program" << std::endl;
        }
        else if (std::regex_match(userInput, listCommand))
        {
            for (int i = 0; i < 4; i++)
            {
                std::cout << items[i].name << " " << items[i].price << std::endl;
            }
        }
        else if (std::regex_match(userInput, buyCommand))
        {
            std::cout << "BUY" << std::endl;
            std::smatch matches;
            std::regex_search(userInput, matches, buyIndividual);

            std::cout << matches[0] << matches[1] << matches[2] << std::endl;
        }
        else if (std::regex_match(userInput, exitCommand))
        {
            inProgram = false;
        }
    }
}