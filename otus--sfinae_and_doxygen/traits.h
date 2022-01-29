#pragma once

#include <tuple>
#include <type_traits>

/**
 * \brief Checks if the object T is at least const iterable
 * 
 * For example, if we have const std::vector<int>, we are
 * not allowed to use iterator, but instead we can use
 * const_iterator. This struct is used to check if it has
 * everything to iterate over T.
 */
template<class T, class = void>
struct is_const_iterable {
    constexpr static bool value = false;
};

/// This SFINAE specialization. Look description in another place...
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




/**
 * \brief Checks if template args have the same type
 * 
 * This meta-function returs true if all the template
 * arguments have the same type or there are 1 or 0 arguments.
 * Otherwise it returns false.
 */
template <class Type, class ...Args>
struct check_type : std::false_type {};

/// This SFINAE specialization. Look description in another place...
template <class Type>
struct check_type <Type> : std::true_type {};

/// This SFINAE specialization. Look description in another place...
template <class Type, class ...Args>
struct check_type <Type, Type, Args...> {
    constexpr static bool value = check_type<Type, Args...>::value;
};

/**
 * \brief Checks if T is a tuple of objects of the same
 * type.
 *
 * This meta-function returs true if T is a tuple of
 * objects of the same type. Examples:
 * T = tuple<int, int> -> true
 * T = tuple<int, char, int> -> false
 * T = tuple<> -> true
 *
 */
template <class T>
struct is_one_type_tuple : std::false_type {};

/// This SFINAE specialization. Look description in another place...
template <>
struct is_one_type_tuple<std::tuple<>> : std::true_type {};

/// This SFINAE specialization. Look description in another place...
template <class T, class ...Args>
struct is_one_type_tuple<std::tuple<T, Args...>> : check_type<T, Args...> {};

template <class T>
constexpr bool is_one_type_tuple_v = is_one_type_tuple<T>::value;


template <class T>
struct is_vector : std::false_type {};

template <class ...Args>
struct is_vector<std::vector<Args...>> : std::true_type {};

template <class T>
constexpr bool is_vector_v = is_vector<T>::value;


template <class T>
struct is_list : std::false_type {};

template <class ...Args>
struct is_list<std::list<Args...>> : std::true_type {};

template <class T>
constexpr bool is_list_v = is_list<T>::value;