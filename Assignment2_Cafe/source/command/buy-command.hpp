#ifndef BUY_COMMAND_H
#define BUY_COMMAND_H

#include "command.hpp"
#include "../menu-item.hpp"
#include "../currency-denomination.hpp"

class BuyCommand final : public Command
{
    public:
        BuyCommand(std::vector<MenuItem>, std::vector<CurrencyDenomination>&);
        std::vector<std::string> GetHelp() override;
    private:
        bool TryParseArgs(std::vector<std::string>) override;
        std::vector<MenuItem> menu;
        std::vector<CurrencyDenomination> wallet;
};

#endif