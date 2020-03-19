#include <gtest/gtest.h>
#include <vector>
#include "../source/money-tools.hpp"
#include "../source/currency-denomination.hpp"

TEST(MoneyTools, CentsToString)
{
    money_tools::set_currency(CURRENCY::USD);

    ASSERT_EQ("$30.09", money_tools::cents_to_string(3009));
    ASSERT_EQ("$5.00", money_tools::cents_to_string(500));
    ASSERT_EQ("$3.10", money_tools::cents_to_string(310));
    ASSERT_EQ("$0.18", money_tools::cents_to_string(18));
    ASSERT_EQ("$0.07", money_tools::cents_to_string(7));
    ASSERT_EQ("$0.00", money_tools::cents_to_string(0));
}

TEST(MoneyTools, CentsToDenominations)
{
    money_tools::set_currency(CURRENCY::USD);

    std::vector<CurrencyDenomination> large_bills = money_tools::cents_to_denominations(47006);
    ASSERT_EQ(8, large_bills.size());
    ASSERT_EQ(10000, large_bills[0].value);
    ASSERT_EQ(10000, large_bills[1].value);
    ASSERT_EQ(10000, large_bills[2].value);
    ASSERT_EQ(10000, large_bills[3].value);
    ASSERT_EQ(5000, large_bills[4].value);
    ASSERT_EQ(2000, large_bills[5].value);
    ASSERT_EQ(5, large_bills[6].value);
    ASSERT_EQ(1, large_bills[7].value);

    std::vector<CurrencyDenomination> large_coins = money_tools::cents_to_denominations(85);
    ASSERT_EQ(4, large_coins.size());
    ASSERT_EQ(25, large_coins[0].value);
    ASSERT_EQ(25, large_coins[1].value);
    ASSERT_EQ(25, large_coins[2].value);
    ASSERT_EQ(10, large_coins[3].value);

    std::vector<CurrencyDenomination> small_coins = money_tools::cents_to_denominations(17);
    ASSERT_EQ(4, small_coins.size());
    ASSERT_EQ(10, small_coins[0].value);
    ASSERT_EQ(5, small_coins[1].value);
    ASSERT_EQ(1, small_coins[2].value);
    ASSERT_EQ(1, small_coins[3].value);

    std::vector<CurrencyDenomination> nickel = money_tools::cents_to_denominations(5);
    ASSERT_EQ(1, nickel.size());
    ASSERT_EQ(5, nickel[0].value);

    std::vector<CurrencyDenomination> pennies = money_tools::cents_to_denominations(3);
    ASSERT_EQ(3, pennies.size());
    ASSERT_EQ(1, pennies[0].value);
    ASSERT_EQ(1, pennies[1].value);
    ASSERT_EQ(1, pennies[2].value);

    std::vector<CurrencyDenomination> empty = money_tools::cents_to_denominations(0);
    ASSERT_EQ(0, empty.size());
}