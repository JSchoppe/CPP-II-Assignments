#include "../input-output.hpp"
#include "buy-command.hpp"
#include "../money-tools.hpp"
#include "../currency-denomination.hpp"

BuyCommand::BuyCommand(std::vector<MenuItem> menu_items, std::vector<CurrencyDenomination>& buyer_wallet)
{
    menu = menu_items;
    wallet = buyer_wallet;
}

std::vector<std::string> BuyCommand::GetHelp()
{
    std::vector<std::string> info;
    info.push_back("buy: spend money to purchase menu items");
    info.push_back("     buy {item name} {item quantity}...");
    info.push_back("     buy burger 1 tea 3");
    return info;
}

bool BuyCommand::TryParseArgs(std::vector<std::string> args)
{
    // Check if there is the correct quantity of arguments.
    if(args.size() < 3) { return false; }
    if(args.size() % 2 == 0) { return false; }
    // Is this a buy command?
    if(args[0] != "buy") { return false; }

    // Scan the remaining arguments for validity.
    std::vector<MenuItem> selected_items;
    std::vector<uint> selected_quantities;
    // Process the args in pairs.
    for(size_t i = 1; i < args.size() - 1; i += 2)
    {
        // Check to see if the requested menu item exists.
        bool match_found = false;
        for(size_t j = 0; j < menu.size(); j++)
        {
            if(menu[j].name == args[i])
            {
                selected_items.push_back(menu[j]);
                match_found = true;
                break;
            }
        }
        if(!match_found) { return false; }

        // Check to see if a valid quantity was entered.
        int quantity = 0;
        try { quantity = std::stoi(args[i + 1]); }
        catch(...) { return false; }
        if(quantity < 1){ return false; }
        selected_quantities.push_back(quantity);
    }

    // Calculate the totals per item and for the entire order(in cents).
    std::vector<uint> totals;
    uint grand_total = 0;
    for(size_t i = 0; i < selected_items.size(); i++)
    {
        totals.push_back(selected_items[i].price * selected_quantities[i]);
        grand_total += totals[i];
    }

    // Generate price strings and calculate the line length
    std::vector<std::string> quantities_as_strings;
    std::vector<std::string> totals_as_strings;
    std::vector<uint> line_lengths;
    uint max_line_length = 0;
    for(size_t i = 0; i < selected_items.size(); i++)
    {
        quantities_as_strings.push_back(std::to_string(selected_quantities[i]) + " " + selected_items[i].name);
        totals_as_strings.push_back(money_tools::cents_to_string(totals[i]));

        uint this_line_length = quantities_as_strings[i].size() + totals_as_strings[i].size();
        if(this_line_length > max_line_length)
        {
            max_line_length = this_line_length;
        }
        line_lengths.push_back(this_line_length);
    }

    // Print the receipt.
    input_output::print_line("RECEIPT:");
    for(size_t i = 0; i < selected_items.size(); i++)
    {
        std::string receipt_line = "";
        receipt_line += quantities_as_strings[i];
        for(uint j = 0; j < max_line_length - line_lengths[i] + 1; j++)
        {
            // Add spacing so all lines end at the same column.
            receipt_line += " ";
        }
        receipt_line += totals_as_strings[i];
        input_output::print_line(receipt_line);
    }
    input_output::print_line("TOTAL: " + money_tools::cents_to_string(grand_total));

    // Prompt the user to pay for the order.
    money_tools::sort_wallet_in_place(wallet);
    std::vector<size_t> pending_wallet_indices;
    uint total_payment_value = 0;
    for(size_t i = 0; i < wallet.size(); i++)
    {
        if(input_output::get_approval("use a " + wallet[i].GetName(false) + "?"))
        {
            pending_wallet_indices.push_back(i);
            total_payment_value += wallet[i].value;
            if(total_payment_value >= grand_total)
            {
                // If the user has provided enough money, stop asking for more.
                break;
            }
        }
    }
    // If the user has not provided enough money, abort the transaction.
    if(total_payment_value < grand_total)
    {
        input_output::print_line("transaction aborted: not enough money");
        return true;
    }

    // Output the receipt footer.
    input_output::print_line("PAID CASH: " + money_tools::cents_to_string(total_payment_value));
    input_output::print_line("CHANGE:    " + money_tools::cents_to_string(total_payment_value - grand_total));
    // Output the returned change.
    input_output::print_line("change recieved:");
    std::vector<CurrencyDenomination> change = money_tools::cents_to_denominations(total_payment_value - grand_total);
    std::vector<std::string> change_strings = money_tools::denominations_to_strings(change);
    input_output::print_multiline(change_strings);

    // Remove the currency pieces from the wallet.
    for(size_t i = pending_wallet_indices.size() - 1; i < pending_wallet_indices.size(); i--)
    {
        wallet.erase(wallet.begin() + pending_wallet_indices[i]);
    }
    // Add the change pieces back to the wallet.
    for(size_t i = 0; i < change.size(); i--)
    {
        wallet.push_back(change[i]);
    }
    // Resort the wallet.
    money_tools::sort_wallet_in_place(wallet);

    return true;
}