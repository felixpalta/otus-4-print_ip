#include "lib.hpp"
#include <iostream>

int main() {
    using namespace otus;

    IpPrinter p(std::cout, "\n");
    p.print(char(-1));
    p.print(short(0));
    p.print(int(2130706433));
    p.print(long(8875824491850138409));
    p.print(std::string("1.2.3.4"));
    p.print(std::vector<int>{192, 168,1, 1});
    p.print(std::list<std::string>{"172", "17", "1", "11"});

    return 0;
}
