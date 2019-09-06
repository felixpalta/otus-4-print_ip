#pragma once

#include <ostream>
#include <type_traits>
#include <vector>
#include <list>

namespace otus {

/**
 * @brief Default (negative) case for string type
 */
template <typename T>
struct is_string_like : public std::false_type
{};

/**
 * @brief Positive case for std::vector type trait
 */
template <>
template <typename CharType, typename Traits, typename Alloc>
struct is_string_like<std::basic_string<CharType, Traits, Alloc>> : public std::true_type
{};

template <>
struct is_string_like<const char *> : public std::true_type
{};

/**
 * @brief Default (negative) case for STL container type trait
 */
template <typename T>
struct is_sequential_container : public std::false_type
{};

/**
 * @brief Positive case for std::vector type trait
 */
template <>
template <typename T, typename Alloc>
struct is_sequential_container<std::vector<T, Alloc>> : public std::true_type
{};

/**
 * @brief Positive case for std::list type trait
 */
template <>
template <typename T, typename Alloc>
struct is_sequential_container<std::list<T, Alloc>> : public std::true_type
{};

/**
 * @brief Class for printing different types of IP adresses
 */
struct IpPrinter
{
    /**
     * @brief IpPrinter
     * @param os Output string stream
     * @param newLine If true, will put new line after print
     */
    IpPrinter(std::ostream & os, std::string lineEnd = std::string()) : _os(os), _lineEnd(lineEnd) {}

    /**
     * @brief Implementation for integral types
     * @param val Input integral value
     */
    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr >
    void print(T val) const {
        typedef typename std::make_unsigned<T>::type value_type;
        value_type uVal = val;
        size_t sz = sizeof(T);
        bool first = true;
        for (size_t i = sz; i > 0; --i) {
            value_type tmp = uVal;
            tmp >>= 8*(i - 1);
            unsigned int octet = tmp & 0xFF;

            if (first)
                first = false;
            else
                _os << ".";
            _os << octet;
        }
        if (!_lineEnd.empty())
            _os << _lineEnd;
    }

    /**
     * @brief Implementation for string IPs
     * @param ip Input string
     */
    template <typename T, std::enable_if_t<is_string_like<T>::value>* = nullptr>
    void print(T ip) const {
        _os << ip;
        if (!_lineEnd.empty())
            _os << _lineEnd;
    }

    /**
     * @brief Implementation for STL sequential containers
     * @param cont Input container
     */
    template <typename T, std::enable_if_t<is_sequential_container<T>::value>* = nullptr>
    void print(T cont) const {
        bool first = true;
        for (const auto & c : cont) {
            if (first)
                first = false;
            else
                _os << ".";
            _os << c;
        }
        if (!_lineEnd.empty())
            _os << _lineEnd;
    }
private:
    std::ostream & _os;
    std::string _lineEnd;
};

} // otus
