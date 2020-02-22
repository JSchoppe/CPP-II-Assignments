#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "MenuItem.cpp"

std::string StringToLower(std::string);
std::vector<std::string> StringSplit(std::string, char);

int main()
{
    // Define recognized input patterns.
    const std::string helpCommand = "help";
    const std::string listCommand = "list";
    const std::string exitCommand = "exit";
    // Define the available menu items.
    const MenuItem items[4] = {
        MenuItem("coffee", 2.15f),
        MenuItem("tea", 2.75f),
        MenuItem("sandwich", 3.50f),
        MenuItem("burger", 5.25f)
    };
    const size_t length = 4;

    // Primary program loop.
    bool inProgram = true;
    while (inProgram)
    {
        // Prompt user.
        std::cout << "Enter a command. Use 'help' to see commands." << std::endl;
        std::string userInput;
        std::getline(std::cin, userInput);
        userInput = StringToLower(userInput);

        // Check user input against commands.
        if (userInput == helpCommand)
        {
            // Show tips for the available commands.
            std::cout << "Available commands:" << std::endl;
            std::cout << "list: shows available menu options" << std::endl;
            std::cout << "{MenuItem} {Quantity}: calculates total cost for an order" << std::endl;
            std::cout << "exit: ends the program" << std::endl;
        }
        else if (userInput == listCommand)
        {
            for (int i = 0; i < length; i++)
            {
                // Print each shop item.
                std::cout << "$" << std::fixed << std::setprecision(2) << items[i].price;
                std::cout << " " << items[i].name << std::endl;
            }
        }
        else if (userInput == exitCommand)
        {
            // Exit program loop.
            inProgram = false;
        }
        else
        {
            // Split the input into chunks.
            std::vector<std::string> inputChunks = StringSplit(userInput, ' ');

            // Are there at least two arguments?
            if(inputChunks.size() >= 2)
            {
                // Initialize arguments to invalid values.
                size_t selectedItemIndex = -1;
                int selectedItemQuantity = -1;

                // Search for the selected menu item.
                for (int i = 0; i < length; i++)
                {
                    if(inputChunks[0] == items[i].name)
                    {
                        selectedItemIndex = i;
                        break;
                    }
                }

                // Try to parse a quantity.
                try
                {
                    selectedItemQuantity = std::stoi(inputChunks[1]);
                }
                catch(...) { }

                // If there was valid input, print the price.
                if(selectedItemIndex != -1 && selectedItemQuantity > 0)
                {
                    // Print each shop item.
                    std::cout << "$" << std::fixed << std::setprecision(2)
                        << items[selectedItemIndex].price * selectedItemQuantity;
                }
            }
        }

        // Add spacing between commands.
        std::cout << std::endl;
    }
}

std::vector<std::string> StringSplit(const std::string toSplit, const char delimiter)
{
    std::vector<std::string> returnVector;
    int length = toSplit.length();
    std::string currentChunk = "";
    for(int i = 0; i < length; i++)
    {
        // Concatenate characters until a delimiter is hit.
        if(toSplit[i] != delimiter)
        {
            currentChunk += toSplit[i];
        }
        else if(currentChunk != "")
        {
            // If the concatenated string has length, push it onto the vector.
            returnVector.push_back(currentChunk);
            currentChunk = "";
        }
    }
    // Check the final check at the end of the string.
    if(currentChunk != "")
    {
        returnVector.push_back(currentChunk);
    }
    return returnVector;
}

std::string StringToLower(const std::string string)
{
    // Convert each character in the string to lowercase.
    std::string returnString = "";
    int length = string.length();
    for(int i = 0; i < length; i++)
    {
        returnString += std::tolower(string[i]);
    }
    return returnString;
}