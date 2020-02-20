#include <string>

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