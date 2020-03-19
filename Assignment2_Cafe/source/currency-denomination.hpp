#ifndef CURRENCY_DENOMINATION_H
#define CURRENCY_DENOMINATION_H

#include <string>

struct CurrencyDenomination final
{
    CurrencyDenomination(uint, std::string, std::string);
    std::string GetName(const bool);
    uint value;
    private:
        std::string singular;
        std::string plural;
};

#endif