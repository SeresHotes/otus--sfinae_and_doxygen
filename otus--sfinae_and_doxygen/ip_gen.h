#pragma once

#include <cinttypes>
#include <iostream>

#include "traits.h"

template<class T,
        typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
void ip_print(std::ostream& out, T&& val) {
    uint8_t* arr = reinterpret_cast<uint8_t*>(&val);
    for (size_t i = sizeof(val) - 1; i > 0; i--) {
        out << +arr[i] << '.';
    }
    out << +arr[0] << std::endl;
}

template<class T,
        typename std::enable_if_t<std::is_convertible_v<T, std::string>, bool> = true>
void ip_print(std::ostream& out, T&& val) {
    out << val << std::endl;
}
 
template<class T,
    typename std::enable_if_t<is_const_iterable_v<T> && !std::is_convertible_v<T, std::string>, bool> = true>
void ip_print(std::ostream& out, T&& val) {
    auto it = val.begin();
    if (val.end() != val.begin()) {
        out << *val.begin();
        ++it;
    }

    for (; it != val.end(); ++it) {
        out << "." << *it;
    }
    out << std::endl;

} 

template<class T, typename std::enable_if_t<is_one_type_tuple_v<T>, bool> = true>
void ip_print(std::ostream& out, T&& val) {
    std::string str = "";
    std::apply([&out, &str](auto&& ...arg) { ((out << str << arg, str = "."), ...); }, val);
    out << std::endl;
}
