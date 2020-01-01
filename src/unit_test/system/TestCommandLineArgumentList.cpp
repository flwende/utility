// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <iostream>
#include <memory>
#include <gtest/gtest.h>

#include <utility/system/CommandLineArguments.hpp>

using ::fw::system::CmdLineArgs;

TEST(CmdLine, ContainsExtraArg)
{
    CmdLineArgs dummy;

    EXPECT_EQ(false, dummy.ContainsKey("-extra-arg"));

    const int argc = 2;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg    ";
    char* argv[argc] = {arg_1, arg_2};
    dummy = {argc, argv};

    EXPECT_EQ(true, dummy.ContainsKey("-extra-arg"));
}

TEST(CmdLine, ExtraArgIndexIs1)
{
    const int argc = 2;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg=";
    char* argv[argc] = {arg_1, arg_2};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(true, dummy.ContainsKey("-extra-arg"));
    EXPECT_EQ(1, dummy.Get("-extra-arg").first);
}

TEST(CmdLine, ExtraArgProvidesValue)
{
    const int argc = 2;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg = 2";
    char* argv[argc] = {arg_1, arg_2};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));
}

TEST(CmdLine, ExtraArgInsertKeyValuePairAfterNotFound)
{
    const int argc = 1;
    char arg_1[] = "x";
    char* argv[argc] = {arg_1};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(false, dummy.ProvidesValue("-extra-arg"));

    dummy.Insert("-extra-arg=2");
    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));
}

TEST(CmdLine, ExtraArgReassignValueToKey)
{
    const int argc = 2;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg = ";
    char* argv[argc] = {arg_1, arg_2};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(false, dummy.ProvidesValue("-extra-arg"));

    dummy.Replace("-extra-arg", "2343");
    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));
}

TEST(CmdLine, ExtraArgSetValueForEmptyKey)
{
    const int argc = 2;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg";
    char* argv[argc] = {arg_1, arg_2};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(false, dummy.ProvidesValue("-extra-arg"));

    dummy.Replace("-extra-arg", "2343");
    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));
}

TEST(CmdLine, ExtraArgSeparatedKeyValuePair)
{
    const int argc = 4;
    char arg_1[] = "x";
    char arg_2[] = "-extra-arg";
    char arg_3[] = "  =";
    char arg_4[] = "3 next=3323";
    char* argv[argc] = {arg_1, arg_2, arg_3, arg_4};
    CmdLineArgs dummy{argc, argv};

    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));

    dummy.Replace("-extra-arg", "2343");
    EXPECT_EQ(true, dummy.ProvidesValue("-extra-arg"));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}