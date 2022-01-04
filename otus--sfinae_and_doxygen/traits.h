#pragma once

#include <tuple>
#include <type_traits>

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

template<class T>
constexpr bool is_const_iterable_v = is_const_iterable<T>::value;





template <class Type, class ...Args>
struct check_type : std::false_type {};

template <class Type>
struct check_type <Type> : std::true_type {};

template <class Type, class ...Args>
struct check_type <Type, Type, Args...> {
    constexpr static bool value = check_type<Type, Args...>::value;
};

template <class Type, class T>
struct check_type_tuple : std::false_type {};

template <class Type, class ...Args>
struct check_type_tuple<Type, std::tuple<Args...>> : check_type<Type, Args...> {};


template <class T>
struct is_one_type_tuple : std::false_type {};

template <>
struct is_one_type_tuple<std::tuple<>> : std::true_type {};

template <class T, class ...Args>
struct is_one_type_tuple<std::tuple<T, Args...>> : check_type<T, Args...> {};

template <class T>
constexpr bool is_one_type_tuple_v = 
    is_one_type_tuple<std::remove_const_t<std::remove_reference_t<T>>>::value;

