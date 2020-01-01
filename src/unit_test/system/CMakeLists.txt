cmake_minimum_required (VERSION 3.0)

add_executable (TestCommandLineArgumentList TestCommandLineArgumentList.cpp ${Sources})
target_link_libraries (TestCommandLineArgumentList LINK_PUBLIC "Utility;gtest;pthread")
