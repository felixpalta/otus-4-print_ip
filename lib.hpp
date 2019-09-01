#pragma once

#include <ostream>
#include <type_traits>
#include <vector>
#include <list>

namespace otus {

template <typename T>
struct is_sequential_container : public std::false_type
{};

template <>
template <typename T, typename Alloc>
struct is_sequential_container<std::vector<T, Alloc>> : public std::true_type
{};

template <>
template <typename T, typename Alloc>
struct is_sequential_container<std::list<T, Alloc>> : public std::true_type
{};

struct IpPrinter
{
    IpPrinter(std::ostream & os, bool newLine = false) : _os(os), _newLine(newLine) {}

    template <typename T, std::enable_if_t<std::is_integral<T>::value, void*> = nullptr >
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
        if (_newLine)
            _os << std::endl;
    }

    void print(const std::string & ip) const {
        _os << ip;
        if (_newLine)
            _os << std::endl;
    }

    template <typename T, std::enable_if_t<is_sequential_container<T>::value, void*> = nullptr>
    void print(T val) const {
        bool first = true;
        for (auto c : val) {
            if (first)
                first = false;
            else
                _os << ".";
            _os << c;
        }
        if (_newLine)
            _os << std::endl;
    }
private:
    std::ostream & _os;
    bool _newLine;
};

} // otus
