#ifndef MONEY_TOOLS_H
#define MONEY_TOOLS_H

#include <string>
#include <vector>
#include "currency-denomination.hpp"

enum class CURRENCY : char
{
    USD
};

struct money_tools final
{
    static void set_currency(const CURRENCY);
    static std::vector<CurrencyDenomination> generate_wallet(std::vector<uint>);
    static std::vector<CurrencyDenomination> get_denominations();
    static std::string cents_to_string(const uint&);
    static std::vector<CurrencyDenomination> cents_to_denominations(uint);
    static uint denominations_to_cents(std::vector<CurrencyDenomination>&);
    static std::vector<std::string> denominations_to_strings(std::vector<CurrencyDenomination>);
    static void sort_wallet_in_place(std::vector<CurrencyDenomination>&);

    private:
        static CURRENCY currency_setting;
        static std::string currency_symbol;
        static bool currency_symbol_precedes;
        static std::vector<CurrencyDenomination> denominations;
};

#endif