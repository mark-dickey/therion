#pragma once

#include <algorithm>
#include <functional>
#include <string_view>
#include <cctype>

namespace detail {

using uchar_type = const unsigned char; // we need to convert chars to unsigned chars because of std::tolower's requirements
using str_it = std::string_view::const_iterator;
using comparator = bool (*)(uchar_type, uchar_type);
using algorithm = bool (*)(str_it, str_it, str_it, str_it, comparator);

template <typename Comparator>
inline bool icase_for_each(std::string_view a, std::string_view b, algorithm alg)
{
    return alg(a.begin(), a.end(), 
               b.begin(), b.end(),
               [](uchar_type ca, uchar_type cb){ return Comparator()(std::tolower(ca), std::tolower(cb)); });
}
}

/**
 * @brief Case insensitive comparison of two strings.
 */ 
inline bool icase_equals(std::string_view a, std::string_view b)
{
     return detail::icase_for_each<std::equal_to<>>(a, b, std::equal);
}

/**
 * @brief Case insensitive ordering of two strings.
 */ 
inline bool icase_less_than(std::string_view a, std::string_view b)
{
     return detail::icase_for_each<std::less<>>(a, b, std::lexicographical_compare);
}
