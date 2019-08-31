#include "lib.hpp"
#include <iostream>
#include <type_traits>

template <typename T>
+void PrintIp(typename std::enable_if<std::is_integral<T>::value, T>::type val) {
    std::cout << val << std::endl;
}

int main() {


    return 0;
}
