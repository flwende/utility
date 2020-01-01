// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#if !defined(STRING_HELPHERS_HPP)
#define STRING_HELPHERS_HPP

#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <utility>

#include <utility/traits/Traits.hpp>

#if !defined(PROJECT_NAMESPACE)
    #define PROJECT_NAMESPACE fw
#endif

namespace PROJECT_NAMESPACE
{
    namespace auxiliary
    {
        auto FindAndReplace(std::string& input, const std::string& find, const std::string& replace, const bool replace_all = false) -> bool;

        auto FindAndReplace(const std::string& input, const std::string& find, const std::string& replace, const bool replace_all = false) -> std::string;

        template <typename... T, typename std::enable_if_t<(std::is_assignable_v<std::string, T> && ...), int> = 0>
        auto Concat(const T&... input) -> std::string
        {
            std::stringstream output;

            (output << ... << input);

            return output.str();
        }

        template <typename T, typename std::enable_if_t<std::is_assignable_v<std::string, T>, int> = 0>
        auto Concat(const std::vector<T>& input, const std::string& separator) -> std::string
        {
            std::stringstream output;
            std::size_t index = 1;
            
            for (const auto& item : input)
            {
                output << (index++ == 1 ? std::string() : separator) << item;
            }

            return output.str();
        }
        
        template <typename... T, typename std::enable_if_t<(IsVector<T>::value && ...), int> = 0>
        auto Concat(const std::string& separator, const T&... input) -> std::string
        {
            const std::array<std::string, sizeof...(T)>& tmp = {Concat(input, separator)...};
            std::stringstream output;
            std::size_t index = 1; 

            for (const auto& substring : tmp)
            {
                if (substring.empty())
                {
                    continue;
                }

                output << (index++ == 1 ? std::string() : separator) << substring;
            }
            
            return output.str();
        }
    }
}

#endif
