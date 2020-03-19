#include <gtest/gtest.h>
#include "../source/utilities.hpp"

TEST(Utilities, StringToLowerInPlace)
{
    std::string caps = "ALL-CAPS";
    std::string no_caps = "no_caps";
    std::string mixed_caps = "mIXXeD caPS";
    std::string empty = "";
    std::string non_alpha = "2020 TO 2030";
    utilities::string_to_lower_in_place(caps);
    utilities::string_to_lower_in_place(no_caps);
    utilities::string_to_lower_in_place(mixed_caps);
    utilities::string_to_lower_in_place(empty);
    utilities::string_to_lower_in_place(non_alpha);

    ASSERT_EQ("all-caps", caps);
    ASSERT_EQ("no_caps", no_caps);
    ASSERT_EQ("mixxed caps", mixed_caps);
    ASSERT_EQ("2020 to 2030", non_alpha);
    ASSERT_EQ("", empty);
}

TEST(Utilities, StringSplit)
{
    std::string empty = "";
    std::string single = "single";
    std::string double_ = "one two";
    std::string triple = "three four FIVE";
    std::string weird_spacing = "  one    two  three ";
    std::string repeat = "one one one one";
    std::vector<std::string> empty_tokens = utilities::string_split(empty);
    std::vector<std::string> single_tokens = utilities::string_split(single);
    std::vector<std::string> double_tokens = utilities::string_split(double_);
    std::vector<std::string> triple_tokens = utilities::string_split(triple);
    std::vector<std::string> weird_spacing_tokens = utilities::string_split(weird_spacing);
    std::vector<std::string> repeat_tokens = utilities::string_split(repeat);

    ASSERT_EQ(0, empty_tokens.size());
    ASSERT_EQ(1, single_tokens.size());
    ASSERT_EQ(2, double_tokens.size());
    ASSERT_EQ(3, triple_tokens.size());
    ASSERT_EQ(3, weird_spacing_tokens.size());
    ASSERT_EQ(4, repeat_tokens.size());

    ASSERT_EQ("single", single_tokens[0]);

    ASSERT_EQ("one", double_tokens[0]);
    ASSERT_EQ("two", double_tokens[1]);

    ASSERT_EQ("three", triple_tokens[0]);
    ASSERT_EQ("four", triple_tokens[1]);
    ASSERT_EQ("FIVE", triple_tokens[2]);

    ASSERT_EQ("one", weird_spacing_tokens[0]);
    ASSERT_EQ("two", weird_spacing_tokens[1]);
    ASSERT_EQ("three", weird_spacing_tokens[2]);

    ASSERT_EQ("one", repeat_tokens[0]);
    ASSERT_EQ("one", repeat_tokens[1]);
    ASSERT_EQ("one", repeat_tokens[2]);
    ASSERT_EQ("one", repeat_tokens[3]);
}