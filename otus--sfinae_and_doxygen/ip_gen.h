#pragma once

#include <cinttypes>
#include <iostream>
#include <tuple>
#include <type_traits>

template<class T,
        typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
void ip_print(std::ostream& out, T val) {
    uint8_t* arr = reinterpret_cast<uint8_t*>(&val);
    for (size_t i = sizeof(val) - 1; i > 0; i--) {
        out << +arr[i] << '.';
    }
    out << +arr[0] << std::endl;
}

template<class T,
        typename std::enable_if_t<std::is_convertible_v<T, std::string>, bool> = true>
void ip_print(std::ostream& out, T val) {
    out << val << std::endl;
}

template<class T, class = void>
struct is_const_iterable {
    constexpr static bool value = false;
};
template<class T>
struct is_const_iterable<T, std::void_t<
    decltype(std::declval<T>().cbegin()),
    decltype(std::declval<T>().cend()),
    decltype(std::declval<T>().cbegin() != std::declval<T>().cend()),
    decltype(++std::declval<T>().cbegin())
    >> {
    constexpr static bool value = true;
};

template<class T, typename V = void>
constexpr bool is_const_iterable_v = typename is_const_iterable<T, V>::value;

template<class T,
    typename std::enable_if_t<is_const_iterable_v<T> && !std::is_convertible_v<T, std::string>, bool> = true>
    void ip_print(std::ostream& out, T val) {
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

//template<class T, class = void>
//struct is_one_type_tuple : std::false_type {}
//template<class T, class = void>
//struct is_one_type_tuple : std::true_type {};
//
//template<class ...Args>
//void ip_print(std::ostream& out, std::tuple<Args...> val) {
//    std::string str = "";
//    //_for_each_tuple([&](int arg) { out << arg << str; str = "."; }, val);
//    std::apply([&out, &str](auto&& ...arg) { ((out << str << arg, str = "."), ...); }, val);
//    out << std::endl;
//}


