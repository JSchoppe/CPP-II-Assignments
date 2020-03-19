#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../source/command/root-command.hpp"

TEST(RootCommandTests, RegistersInput)
{
    // Should just return true when the help argument is matched.
    RootCommand command = RootCommand("help", "displays available commands");

    ASSERT_TRUE(command.TryParseStringArgs("help"));
    ASSERT_TRUE(command.TryParseStringArgs("HELP"));
    ASSERT_TRUE(command.TryParseStringArgs("HeLp"));
    ASSERT_TRUE(command.TryParseStringArgs("  help    "));

    ASSERT_FALSE(command.TryParseStringArgs("-help"));
    ASSERT_FALSE(command.TryParseStringArgs("h e l p"));
    ASSERT_FALSE(command.TryParseStringArgs("Help?"));

    ASSERT_EQ("help: displays available commands", (command.GetHelp())[0]);
}