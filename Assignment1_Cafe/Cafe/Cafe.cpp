#include <iostream>
#include <iomanip>
#include <string>
#include <regex>

struct MenuItem
{
    std::string name;
    float price;
    MenuItem(std::string _name, float _price)
    {
        name = _name;
        price = _price;
    }
};

int main()
{
    // Define recognized input patterns.
    std::regex helpCommand("^((H|h)elp|HELP)$");
    std::regex listCommand("^((L|l)ist|LIST)$");
    std::regex exitCommand("^((E|e)xit|EXIT)$");
    std::regex buyCommand("^([A-Za-z]+\\s[0-9]+(\\s)*)+$");
    // Define the available menu items.
    MenuItem items[4] = {
        MenuItem("Coffee", 2.15f),
        MenuItem("Tea", 2.75f),
        MenuItem("Sandwich", 3.50f),
        MenuItem("Burger", 5.25f)
    };

    // Primary program loop.
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
            // Show tips for the available commands.
            std::cout << "Available commands:" << std::endl;
            std::cout << "list: shows available menu options" << std::endl;
            std::cout << "{MenuItem} {Quantity}: calculates total cost for an order" << std::endl;
            std::cout << "exit: ends the program" << std::endl;
        }
        else if (std::regex_match(userInput, listCommand))
        {
            size_t length = sizeof(items) / sizeof(items[0]);
            for (int i = 0; i < length; i++)
            {
                // Print each shop item.
                std::cout << "$" << std::fixed << std::setprecision(2) << items[i].price;
                std::cout << " " << items[i].name << std::endl;
            }
        }
        else if (std::regex_match(userInput, buyCommand))
        {
            float totalPrice = 0;

            // Define patterns for matching command arguments.
            std::regex itemQuantityExp("[A-Za-z]+\\s[0-9]+");
            std::regex itemExp("[A-Za-z]+");
            std::regex quantityExp("[0-9]+");

            // Match all item quantity pairs.
            std::smatch itemQuantityMatch;
            do
            {
                // Advance to the next expression pair.
                std::regex_search(userInput, itemQuantityMatch, itemQuantityExp);
                std::string itemQuantityPair = itemQuantityMatch[0];

                // Extract the components of this pair.
                std::smatch itemMatch, quantityMatch;
                std::regex_search(itemQuantityPair, itemMatch, itemExp);
                std::regex_search(itemQuantityPair, quantityMatch, quantityExp);
                std::string item = itemMatch[0];
                int quantity = std::stoi(quantityMatch[0]);

                if (quantity > 0)
                {
                    // Search for this shop item.
                    size_t length = sizeof(items) / sizeof(items[0]);
                    for (int i = 0; i < length; i++)
                    {
                        if (items[i].name == item)
                        {
                            // Print receipt line.
                            std::cout << "$" << std::fixed << std::setprecision(2) << items[i].price;
                            std::cout << " X " << quantity << " " << item << std::endl;
                            totalPrice += items[i].price * quantity;
                            break;
                        }
                    }
                }

                // Move past this expression pair.
                userInput = itemQuantityMatch.suffix();
            } while (userInput != "");

            // If any item matches were found print the total.
            if (totalPrice > 0)
            {
                std::cout << "TOTAL: $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;
            }
        }
        else if (std::regex_match(userInput, exitCommand))
        {
            // Exit program loop.
            inProgram = false;
        }

        // Add spacing between commands.
        std::cout << std::endl;
    }
}