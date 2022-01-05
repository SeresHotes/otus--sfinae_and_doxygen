#pragma once

#include <cinttypes>
#include <iostream>

#include "traits.h"
/**
 * \brief Prints numbers in ip format
 *
 * This function can accept val of folowing types:
 * 1) integral
 * 2) std::string
 * 3) iterable
 * 4) std::tuple<Args...>, where Args.. have all the same type
 *
 */
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

template<class T, 
    typename std::enable_if_t<is_one_type_tuple_v<std::remove_const_t<std::remove_reference_t<T>>>, bool> = true>
void ip_print(std::ostream& out, T&& val) {
    std::string str = "";
    std::apply([&out, &str](const auto& ...arg) { ((out << str << arg, str = "."), ...); }, val);
    out << std::endl;
}
