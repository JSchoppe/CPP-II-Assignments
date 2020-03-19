#include "menu-item.hpp"

MenuItem::MenuItem(std::string item_name, uint item_price_cents)
{
    name = item_name;
    price = item_price_cents;
}