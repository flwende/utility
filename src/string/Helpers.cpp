// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <cstdint>

#include <utility/string/Helpers.hpp>

namespace PROJECT_NAMESPACE
{
    namespace auxiliary
    {
        auto FindAndReplace(std::string& input, const std::string& assumed, const std::string& replacement, const bool replace_all) -> bool
        {
            bool return_value = false;
            std::size_t pos = input.find(assumed);

            while (pos != std::string::npos)
            {
                input.replace(pos, assumed.length(), replacement);
                return_value = true;

                if (!replace_all)
                {
                    break;
                }

                pos = input.find(assumed, pos + replacement.length());
            }

            return return_value;
        }

        auto FindAndReplace(const std::string& input, const std::string& assumed, const std::string& replacement, const bool replace_all) -> std::string
        {
            std::string output{input};

            FindAndReplace(output, assumed, replacement, replace_all);

            return output;
        }
    }
}
