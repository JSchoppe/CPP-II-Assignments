#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

struct MenuItem final
{
    MenuItem(std::string, uint);
    std::string name;
    uint price;
};

#endif