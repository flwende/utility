// Copyright (c) 2020 Florian Wende (flwende@gmail.com)
//
// Distributed under the BSD 2-clause Software License
// (See accompanying file LICENSE)

#if !defined(AUXILIARY_TRAITS_HPP)
#define AUXILIARY_TRAITS_HPP

#include <array>
#include <map>
#include <set>
#include <vector>
#include <type_traits>
#include <utility>

#if !defined(PROJECT_NAMESPACE)
    #define PROJECT_NAMESPACE fw
#endif

namespace PROJECT_NAMESPACE
{
    namespace auxiliary
    {
        // Container traits.
        template <typename T>
        struct IsArray
        {
            static constexpr bool value = false;
        };

        template <typename... T>
        struct IsArray<std::array<T...>>
        {
            static constexpr bool value = true;
        };

        template <typename T>
        struct IsMap
        {
            static constexpr bool value = false;
        };

        template <typename... T>
        struct IsMap<std::map<T...>>
        {
            static constexpr bool value = true;
        };

        template <typename T>
        struct IsSet
        {
            static constexpr bool value = false;
        };

        template <typename... T>
        struct IsSet<std::set<T...>>
        {
            static constexpr bool value = true;
        };

        template <typename T>
        struct IsVector
        {
            static constexpr bool value = false;
        };

        template <typename... T>
        struct IsVector<std::vector<T...>>
        {
            static constexpr bool value = true;
        };

        template <typename T>
        struct IsIteratable
        {
            static constexpr bool value = IsArray<T>::value || IsMap<T>::value || IsSet<T>::value || IsVector<T>::value;
        };

        template <typename T>
        struct IsPair
        {
            static constexpr bool value = false;
        };

        template <typename T_1, typename T_2>
        struct IsPair<std::pair<T_1, T_2>>
        {
            static constexpr bool value = true;
        };
    }
}

#endif
