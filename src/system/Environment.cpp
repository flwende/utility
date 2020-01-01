// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <utility/system/Environment.hpp>

namespace PROJECT_NAMESPACE
{
    namespace system
    {
        auto GetEnv(const std::string& variable_name) -> const char*
        {
            return std::getenv(variable_name.c_str());
        }
    }
}