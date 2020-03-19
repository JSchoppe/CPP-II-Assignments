#include "money-tools.hpp"

CURRENCY money_tools::currency_setting;
std::string money_tools::currency_symbol;
bool money_tools::currency_symbol_precedes;
std::vector<CurrencyDenomination> money_tools::denominations;

void money_tools::set_currency(const CURRENCY currency_type)
{
    switch(currency_type)
    {
        case CURRENCY::USD:
            currency_setting = CURRENCY::USD;
            currency_symbol = "$";
            currency_symbol_precedes = true;
            denominations = std::vector<CurrencyDenomination>
            {
                CurrencyDenomination(1, "penny", "pennies"),
                CurrencyDenomination(5, "nickel", "nickels"),
                CurrencyDenomination(10, "dime", "dimes"),
                CurrencyDenomination(25, "quarter", "quarters"),
                CurrencyDenomination(100, "dollar bill", "dollar bills"),
                CurrencyDenomination(500, "five dollar bill", "five dollar bills"),
                CurrencyDenomination(1000, "ten dollar bill", "ten dollar bills"),
                CurrencyDenomination(2000, "twenty dollar bill", "twenty dollar bills"),
                CurrencyDenomination(5000, "fifty dollar bill", "fifty dollar bills"),
                CurrencyDenomination(10000, "hundred dollar bill", "hundred dollar bills")
            };
            break;
    }
}

std::vector<CurrencyDenomination> money_tools::generate_wallet(std::vector<uint> values)
{
    std::vector<CurrencyDenomination> wallet;

    // Match each value to its currency piece.
    size_t size = values.size();
    size_t denom_size = denominations.size();
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < denom_size; j++)
        {
            if(denominations[j].value == values[i])
            {
                // Add the currency piece to the wallet.
                wallet.push_back(denominations[j]);
                break;
            }
        }
    }

    return wallet;
}

std::vector<CurrencyDenomination> money_tools::get_denominations()
{
    return denominations;
}

std::string money_tools::cents_to_string(const uint& total_cents)
{
    // Break the total cents into dollars and cents.
    uint dollars = total_cents / 100;
    uint cents = total_cents % 100;

    std::string str = "";

    if(currency_symbol_precedes){ str += currency_symbol; }

    // Place the amount of dollars before the decimal.
    str += std::to_string(dollars);
    str += ".";
    // Format cents so it is always printed in two decimal places.
    if(cents == 0){ str += "00"; }
    else if(cents < 10){ str += "0"; str += std::to_string(cents); }
    else{ str += std::to_string(cents); }

    if(!currency_symbol_precedes){ str += currency_symbol; }

    return str;
}

std::vector<CurrencyDenomination> money_tools::cents_to_denominations(uint total_cents)
{
    std::vector<CurrencyDenomination> pieces;

    // Work backwards through the higher denominations.
    size_t size = denominations.size();
    for(size_t i = size - 1; i < size; i--)
    {
        // How many of the denomination can be taken out of the total?
        uint quantity = total_cents / denominations[i].value;
        // Add that many, and subtract from the total cents.
        for(uint j = 0; j < quantity; j++)
        {
            pieces.push_back(denominations[i]);
            total_cents -= denominations[i].value;
        }
    }

    return pieces;
}

uint money_tools::denominations_to_cents(std::vector<CurrencyDenomination>& pieces)
{
    uint accumulator = 0;

    // Count the value of all currency pieces.
    size_t size = pieces.size();
    for(size_t i = 0; i < size; i++)
    {
        accumulator += pieces[i].value;
    }

    return accumulator;
}

std::vector<std::string> money_tools::denominations_to_strings(std::vector<CurrencyDenomination> pieces)
{
    // Reorder the currency pieces from greatest to least.
    money_tools::sort_wallet_in_place(pieces);

    std::vector<std::string> strings;
    size_t size = pieces.size();

    // Handle edge cases with 0 or 1 currency pieces.
    if(size == 0) { return strings; }
    else if(size == 1)
    {
        strings.push_back("1 " + pieces[0].GetName(false));
        return strings;
    }

    // Scan the vector looking for groups of denominations.
    CurrencyDenomination current_denomination = pieces[0];
    uint quantity = 1;
    for(size_t i = 1; i < size; i++)
    {
        if(pieces[i].value == current_denomination.value)
        {
            // Same as last denomination.
            quantity++;
        }
        else
        {
            // Different from last denomination.
            strings.push_back(std::to_string(quantity) + " " + current_denomination.GetName(quantity > 1));
            // Reset logic.
            current_denomination = pieces[i];
            quantity = 1;
        }
    }
    // Push the final denomination group.
    strings.push_back(std::to_string(quantity) + " " + current_denomination.GetName(quantity > 1));

    return strings;
}

void money_tools::sort_wallet_in_place(std::vector<CurrencyDenomination>& wallet)
{
    // Bubble sort to bring higher currency pieces to the front of the wallet.
    size_t size = wallet.size();
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = i; j > 0; j--)
        {
            if(wallet[j].value > wallet[j-1].value)
            {
                std::swap(wallet[j], wallet[j-1]);
            }
        }
    }
}