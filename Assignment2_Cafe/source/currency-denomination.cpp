#include "currency-denomination.hpp"

CurrencyDenomination::CurrencyDenomination(uint value_cents, std::string name_singular, std::string name_plural)
{
    value = value_cents;
    singular = name_singular;
    plural = name_plural;
}

std::string CurrencyDenomination::GetName(const bool isPlural)
{
    return isPlural? plural : singular;
}