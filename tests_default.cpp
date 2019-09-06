#include <gtest/gtest.h>
#include "lib.hpp"
#include <sstream>

class OssFixture :  public ::testing::Test {
public:
    OssFixture() : p(oss) {}
protected:
    std::ostringstream oss;
    const otus::IpPrinter p;
};

TEST_F(OssFixture, CharTest) {
    p.print(char(-1));
    ASSERT_EQ("255", oss.str());
}

TEST_F(OssFixture, ShortTest) {
    p.print(short(3085));
    ASSERT_EQ("12.13", oss.str());
}

TEST_F(OssFixture, IntTest) {
    p.print(int(std::numeric_limits<int>::max()));
    ASSERT_EQ("127.255.255.255", oss.str());
}

TEST_F(OssFixture, StringTest) {
    auto s = "foobar";
    p.print(s);
    ASSERT_EQ(s, oss.str());
}

TEST_F(OssFixture, VectorTest) {
    std::vector<int> v = {127, 0, 0 ,1};
    p.print(v);
    ASSERT_EQ("127.0.0.1", oss.str());
}

TEST_F(OssFixture, ListTest) {
    std::list<int> l = {192, 168,0, 1};
    p.print(l);
    ASSERT_EQ("192.168.0.1", oss.str());
}
