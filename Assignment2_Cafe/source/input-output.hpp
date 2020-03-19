#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>
#include <vector>
#include "command/command.hpp"

struct input_output final
{
    static std::string get_input();
    static bool get_approval(const std::string&);
    static void print_line(const std::string&);
    static void print_line();
    static void print_multiline(std::vector<std::string>&);
    static void print_command_tree(const std::vector<Command*>&);
};

#endif