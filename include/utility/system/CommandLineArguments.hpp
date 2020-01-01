// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#if !defined(SYSTEM_COMMANDLINEARGUMENTS_HPP)
#define SYSTEM_COMMANDLINEARGUMENTS_HPP

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#if !defined(PROJECT_NAMESPACE)
#define PROJECT_NAMESPACE fw
#endif

namespace PROJECT_NAMESPACE
{
    namespace system
    {
        //!
        //! \brief This type holds a copy of some command line arguments.
        //!
        class CmdLineArgs
        {
            auto FindFirstNotOf(const std::string& find_string, const int index, const std::size_t offset = 0) const -> std::pair<int, int>;
            
            auto FindValueStartPosition(const std::string& key) const -> std::pair<int, int>;

        public:
            CmdLineArgs() : argc{}, argv{} {}

            CmdLineArgs(int_fast64_t argc, char** argv);

            auto Argc() const -> const int&;

            auto Argc() -> int&;

            auto Argv() const -> const char**;

            auto Get(const std::string& key) const -> std::pair<int, const char*>;

            auto ContainsKey(const std::string& key) const -> bool;

            auto ProvidesValue(const std::string& key) const -> bool;

            auto Insert(const std::string& arg) -> CmdLineArgs&;

            auto Replace(const std::string& key, const std::string& value) -> CmdLineArgs&;

            void Print() const;

        protected:
            int argc;
            std::unique_ptr<const char*[]> argv;
            std::vector<std::unique_ptr<char>> additional_args;
        };
    }
}

#endif