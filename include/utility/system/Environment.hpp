// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#if !defined(SYSTEM_ENVIRONMENT_HPP)
#define SYSTEM_ENVIRONMENT_HPP

#include <cstdlib>
#include <string>
#include <type_traits>

#if !defined(PROJECT_NAMESPACE)
    #define PROJECT_NAMESPACE fw
#endif

namespace PROJECT_NAMESPACE
{
    namespace system
    {
        auto GetEnv(const std::string& variable_name) -> const char*;

        template <typename T>
        auto GetEnv(const std::string& variable_name, const T& default_value) -> T
        {
            if (const char* value = GetEnv(variable_name))
            {
                if constexpr (std::is_floating_point_v<T>)
                {
                    return std::atof(value);
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    return std::atoi(value);
                }
            }

            return default_value;
        }
    }
}

#endif