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

template <typename T, std::enable_if_t<std::is_integral<T>::value, void*> = nullptr >
void PrintIp(T val) {
    std::cout << val << std::endl;
}

void PrintIp(const std::string & ip) {
    std::cout << ip << std::endl;
}

template <typename T, std::enable_if_t<is_sequential_container<T>::value, void*> = nullptr>
void PrintIp(T val) {
    bool first = true;
    for (auto c : val) {
        if (first)
            first = false;
        else
            std::cout << ".";
        std::cout << c;
    }
    std::cout << std::endl;
}

int main() {

    PrintIp(99);
    PrintIp("wololo");
    PrintIp(std::vector<int>{1, 2, 3, 99});
    PrintIp(std::list<char>{'a', 'b', 'c'});

    return 0;
}
