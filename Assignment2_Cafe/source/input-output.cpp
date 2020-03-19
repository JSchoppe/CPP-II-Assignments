#include <iostream>
#include "input-output.hpp"
#include "utilities.hpp"

std::string input_output::get_input()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool input_output::get_approval(const std::string& request)
{
    std::cout << request << " [y/n] ";
    while(true)
    {
        std::string user_input = input_output::get_input();
        utilities::string_to_lower_in_place(user_input);

        if(user_input == "y"){ return true; }
        else if(user_input == "n"){ return false; }
    }
}

void input_output::print_line(const std::string& line)
{
    std::cout << line << std::endl;
}
void input_output::print_line()
{
    std::cout << std::endl;
}

void input_output::print_multiline(std::vector<std::string>& lines)
{
    size_t size = lines.size();
    for(size_t i = 0; i < size; i++)
    {
        std::cout << lines[i] << std::endl;
    }
}

void input_output::print_command_tree(const std::vector<Command*>& commands)
{
    std::cout << "Available Commands:" << std::endl;

    // Print out information on all commands.
    size_t size = commands.size();
    for(size_t i = 0; i < size; i++)
    {
        std::vector<std::string> info = commands[i]->GetHelp();
        input_output::print_multiline(info);
    }
}