#include "lib.hpp"
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

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
    IpPrinter(std::ostream & os) : _os(os) {}

    template <typename T, std::enable_if_t<std::is_integral<T>::value, void*> = nullptr >
    void print(T val) {
        typedef typename std::make_unsigned<T>::type value_type;
        value_type uVal = val;
        size_t sz = sizeof(T);
        bool first = true;
        for (size_t i = sz; i > 0; --i) {
            value_type tmp = uVal;
            tmp >>= i - 1;
            unsigned int octet = tmp && 0xFF;

            if (first)
                first = false;
            else
                _os << ".";
            _os << octet;
        }
        _os << std::endl;
    }

    void print(const std::string & ip) {
        _os << ip << std::endl;
    }

    template <typename T, std::enable_if_t<is_sequential_container<T>::value, void*> = nullptr>
    void print(T val) {
        bool first = true;
        for (auto c : val) {
            if (first)
                first = false;
            else
                _os << ".";
            _os << c;
        }
        _os << std::endl;
    }
private:
    std::ostream & _os;
};

int main() {
    IpPrinter p(std::cout);
    p.print(int(2130706433));
    p.print("wololo");
    p.print(std::vector<int>{1, 2, 3, 99});
    p.print(std::list<char>{'a', 'b', 'c'});

    return 0;
}
