// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#include <utility/system/CommandLineArguments.hpp>

namespace PROJECT_NAMESPACE
{
    namespace system
    {
        CmdLineArgs::CmdLineArgs(int_fast64_t argc, char** argv)
            :
            argc(argc),
            argv([argc, &argv]()
                {
                    std::unique_ptr<const char*[]> tmp(new const char*[argc]);
                    const char** ptr = tmp.get();

                    for (int i = 0; i < argc; ++i)
                    { 
                        ptr[i] = argv[i];
                    }

                    return tmp;
                }())
        {}

        auto CmdLineArgs::FindFirstNotOf(const std::string& find_string, const int index, const std::size_t offset) const
            -> std::pair<int, int>
        {
            if (index >= 0 && index < argc)
            {
                const std::size_t pos = std::string(argv[index]).find_first_not_of(find_string, offset);

                // Move on to the next argument if not found.
                if (pos == std::string::npos)
                {
                    return FindFirstNotOf(find_string, index + 1);
                }

                // Found.
                return {index, pos};
            }

            // Not found.
            return {-1, -1};
        }

        auto CmdLineArgs::FindValueStartPosition(const std::string& key) const
            -> std::pair<int, int>
        {   
            // Consider everything that follows the key.
            const int key_index = Get(key).first;
            auto [sign_index, sign_pos] = FindFirstNotOf(" ", key_index, key.length());

            // Check if the first character that is not a whitespace is '='.
            if (sign_pos >= 0 && std::string(argv[sign_index]).at(sign_pos) == '=')
            {
                // Consider everything that follows the sign.
                auto [value_index, value_pos] = FindFirstNotOf(" ", sign_index, sign_pos + 1);

                // Check if the first character that is not a whitespace is not '='.
                if (value_pos >= 0 && std::string(argv[value_index]).at(value_pos) != '=')
                {
                    // Value found.
                    return {value_index, value_pos};
                }
            }

            // No value found, but maybe the key has been found: return the `key_index` therefore.
            return {key_index, -1};
        }

        auto CmdLineArgs::Argc() const -> const int&
        { 
            return argc;
        }

        auto CmdLineArgs::Argc() -> int&
        { 
            return argc;
        }

        auto CmdLineArgs::Argv() const -> const char** 
        { 
            return argv.get();
        }

        auto CmdLineArgs::Get(const std::string& key) const
            -> std::pair<int, const char*>
        {
            if (!key.empty())
            {
                // Go thorugh all arguments until the `key` matches.
                for (int i = 0; i < argc; ++i)
                {
                    const std::string arg(argv[i]);

                    if (arg.find(key) == 0)
                    {
                        // Make sure that after the `key` is no other character except a sign '='.
                        const std::size_t pos = arg.find_first_not_of(" ", key.length());

                        if (pos == std::string::npos || arg.at(pos) == '=')
                        {
                            return {i, arg.c_str()};
                        }
                    }   
                }
            }

            // The `key` has not been found.
            return {-1, nullptr};
        }

        auto CmdLineArgs::ContainsKey(const std::string& key) const -> bool 
        { 
            return (Get(key).first >= 0);
        }

        auto CmdLineArgs::ProvidesValue(const std::string& key) const -> bool
        { 
            return (FindValueStartPosition(key).second >= 0);
        }

        auto CmdLineArgs::Insert(const std::string& arg)
            -> CmdLineArgs&
        {
            std::unique_ptr<const char*[]> tmp(new const char*[argc + 1]);
            for (int i = 0; i < argc; ++i)
            {
                tmp[i] = argv[i];
            }

            additional_args.emplace_back(new char[arg.length() + 1]);
            std::memcpy(additional_args.back().get(), arg.c_str(), arg.length());
            additional_args.back().get()[arg.length()] = '\0';

            tmp[argc++] = additional_args.back().get();
            argv.swap(tmp);

            return *this;
        }

        auto CmdLineArgs::Replace(const std::string& key, const std::string& value)
            -> CmdLineArgs&
        {
            auto [key_index, value_pos] = FindValueStartPosition(key);
            
            // If the `key` has been found, assign the value or update it.
            if (key_index >= 0)
            {
                std::string arg = std::string(argv[key_index]);
        
                // Update the assignment.
                if (value_pos >= 0)
                {
                    // Get the length of the current value.
                    const std::size_t next_space = arg.find(' ', value_pos);

                    // Replace the current value by the new `value`.
                    arg.replace(arg.begin() + value_pos, (next_space == std::string::npos ? arg.end() : arg.begin() + next_space), value);
                }
                // Assign the `value`.
                else
                {
                    arg.replace(arg.begin() + key.length(), arg.end(), "=" + value);
                }        
                
                additional_args.emplace_back(new char[arg.length()]);
                std::memcpy(additional_args.back().get(), arg.c_str(), arg.length());
                argv[key_index] = additional_args.back().get();

                return *this;
            }
            // Append both the `key` and the `value`.
            else
            {
                //return Insert(key, value);
                return Insert(key + "=" + value);
            }
        }

        void CmdLineArgs::Print() const
        {
            for (int i = 0; i < argc; ++i)
            {
                std::cout << argv[i] << std::endl;
            }
        }
    }
}